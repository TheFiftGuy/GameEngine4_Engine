#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>
#include <string>
#include <fstream>

class Debug	{
public:
	enum class MessageType : unsigned short {
		TYPE_NONE = 0,
		TYPE_FATAL_ERROR,
		TYPE_ERROR,
		TYPE_WARNING,
		TYPE_TRACE,
		TYPE_INFO
	};

	Debug() = delete; //no instance of debug allowed
	Debug(const Debug&) = delete;
	Debug(Debug&&) = delete;
	Debug& operator=(const Debug&) = delete;
	Debug& operator = (Debug&&) = delete;

	static void OnCreate(const std::string& name_ = "Game258EngineLog");
	static void SetSeverity(MessageType type_);
	static void Info(const std::string& message_, const std::string& fileName_, const int line_);
	static void Trace(const std::string& message_, const std::string& fileName_, const int line_);
	static void Warning(const std::string& message_, const std::string& fileName_, const int line_);
	static void Error(const std::string& message_, const std::string& fileName_, const int line_);
	static void FatalError(const std::string& message_, const std::string& fileName_, const int line_);

private:
	static void Log(const MessageType type_, const std::string& message_,
		const std::string& fileName_, const int Line_);
	static MessageType currentSev;
	static std::string outputName;

};

#endif