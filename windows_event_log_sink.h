#ifndef GLOG_WINDOWS_EVENT_LOG_SINK_
#define GLOG_WINDOWS_EVENT_LOG_SINK_

#include <dbghelp.h>
#include <string>

#include "endgame.pb.h"
#include "glog/logging.h"
#include "google/protobuf/util/json_util.h"

namespace glog {

// Sink for windows event logs
class WindowsEventLogSink : public google::LogSink {
public:
  virtual ~WindowsEventLogSink() {
    if (event_log_) {
      DeregisterEventSource(event_log_);
    }
  }

  WindowsEventLogSink() {
    OutputDebugStringA("Starting WindowsEventLogSink");
    auto session_token = getenv("ENDGAME_SESSION_TOKEN");
    auto username = getenv("ENDGAME_USER");
    if (username != nullptr) {
      username_ = username;
    } else {
      username_ = "UNKNOWN";
    }
    if (session_token != nullptr) {
      session_token_ = std::string(session_token);
    }
    std::string session_str = "EndGameSession" + session_token_;
    event_log_ = RegisterEventSource(NULL, session_str.c_str());
    port_opened_ = false;
  }

  void SetSessionId(const std::string& sessionid) {
    session_token_ = sessionid;
  }

  void SetProcName(const std::string &proc_name) {
    proc_name_ = proc_name;
  }

  void SetNodeName(const std::string &node_name) {
    node_name_ = node_name;
  }

  void OpenLogUpdatePort() {
    if (port_opened_)
      return;
    port_opened_ = true;
    WSAData data;
    int ret = WSAStartup(MAKEWORD(2, 2), &data);
    if (ret != 0) {
      LOG(WARNING) << "WSAStartup failed with " << ret;
    }

    sock_ = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock_ == INVALID_SOCKET) {
      LOG(ERROR) << "Socket creation failed";
      return;
    }

    memset(&servaddr_, 0, sizeof(servaddr_));
    servaddr_.sin_family = AF_INET;
    auto portstr = getenv("ENDGAME_LOGUPLOAD_PORT");
    if (portstr != nullptr) {
      servaddr_.sin_port = htons(atoi(portstr));
    } else {
      // TODO : This constat is replicated in pubsuborch/log_upload.cc
      static const int kLogUploadPort = 11000;
      servaddr_.sin_port = htons(kLogUploadPort);
    }
    servaddr_.sin_addr.s_addr = inet_addr("127.0.0.1");
    LOG(INFO) << "Sending logs to UDP port";

    options_.add_whitespace = true;
    options_.always_print_primitive_fields = true;
    options_.preserve_proto_field_names = true;
  }

  virtual void send(google::LogSeverity severity, const char *full_filename,
                    const char *base_filename, int line,
                    const struct ::tm *tm_time, const char *message,
                    size_t message_len) {
    if (event_log_) {
      std::string full_msg = std::string(base_filename) +
                             ":" + std::to_string(line) + " " +
                             std::string(message, message_len);
      const char *msg_strings[] = {full_msg.c_str()};

      if (!port_opened_) {
        OpenLogUpdatePort();
      }

      if (sock_ != INVALID_SOCKET) {
        endgame::LogMessage lm;
        lm.set_sessionid(session_token_);
        lm.set_username(username_);
        if (severity == google::GLOG_INFO) {
          lm.set_severity("INFO");
        } else if (severity == google::GLOG_WARNING) {
          lm.set_severity("WARNING");
        } else if (severity == google::GLOG_ERROR) {
          lm.set_severity("ERROR");
        }
        lm.set_filename(base_filename);
        lm.set_linenum(std::to_string(line));
        lm.set_logmsg(full_msg);
        lm.set_procname(proc_name_);
        lm.set_hostname(node_name_);

        std::string jsonstr;
        MessageToJsonString(lm, &jsonstr, options_);

        sendto(sock_, (const char *)jsonstr.c_str(), jsonstr.size(), 0,
               (const struct sockaddr *)&servaddr_, sizeof(servaddr_));
      }

      DWORD type;
      if (severity == google::GLOG_INFO) {
        type = EVENTLOG_INFORMATION_TYPE;
      } else if (severity == google::GLOG_INFO) {
        type = EVENTLOG_WARNING_TYPE;
      } else {
        type = EVENTLOG_ERROR_TYPE;
      }
      ReportEvent(event_log_, type, 0, 0, NULL, 1, 0, msg_strings, NULL);
    }
  }

  virtual void WaitTillSent() {}

private:
  std::string session_token_;
  std::string proc_name_;
  std::string node_name_;
  std::string username_;
  HANDLE event_log_ = nullptr;
  SOCKET sock_ = INVALID_SOCKET;
  struct sockaddr_in servaddr_;
  google::protobuf::util::JsonPrintOptions options_;
  bool port_opened_;
};

} // namespace glog
#endif // GLOG_WINDOWS_EVENT_LOG_SINK_
