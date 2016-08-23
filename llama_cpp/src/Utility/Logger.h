//
//  Logger.h
//  Project-LLama
//
//  Created by BlueCocoa on 2016/8/22.
//  Copyright © 2016 BlueCocoa. All rights reserved.
//

#ifndef LLAMA_CPP_SRC_UTILITY_LOGGER_H_
#define LLAMA_CPP_SRC_UTILITY_LOGGER_H_

#include <Utility/module_check.h>
#include <stdlib.h>
#include <fstream>
#include <mutex>
#include <ostream>
#include <string>
#include <thread>
#include <type_traits>
#include <utility>

#define LLAMA_LOG_LEVEL_DEBUG   1
#define LLAMA_LOG_LEVEL_INFO    2
#define LLAMA_LOG_LEVEL_WARNING 3
#define LLAMA_LOG_LEVEL_ERROR   4
#define LLAMA_LOG_LEVEL_ERROR_X 5
#define LLAMA_LOG_LEVEL_NOTHING 6

#ifndef LLAMA_LOG_LEVEL
    #define LLAMA_LOG_LEVEL LLAMA_LOG_LEVEL_DEBUG
#elif((LLAMA_LOG_LEVEL < LLAMA_LOG_LEVEL_DEBUG) || (LLAMA_LOG_LEVEL > LLAMA_LOG_LEVEL_ERROR_X))
    #define LLAMA_LOG_LEVEL LLAMA_LOG_LEVEL_NOTHING
#endif

#ifdef LLAMA_LOG_ENABLE_FILE_LINE
    #define LLAMA_LOG_DEBUG(logger, ...)    logger.debugWrapper  (__FILE__, ": ", __LINE__, ": ", __VA_ARGS__);
    #define LLAMA_LOG_INFO(logger, ...)     logger.infoWrapper   (__FILE__, ": ", __LINE__, ": ", __VA_ARGS__);
    #define LLAMA_LOG_WARNING(logger, ...)  logger.warningWrapper(__FILE__, ": ", __LINE__, ": ", __VA_ARGS__);
    #define LLAMA_LOG_ERROR(logger, ...)    logger.errorWrapper  (__FILE__, ": ", __LINE__, ": ", __VA_ARGS__);
    #define LLAMA_LOG_ERROR_X(logger, ...)  logger.error_xWrapper(__FILE__, ": ", __LINE__, ": ", __VA_ARGS__);
#else
    #define LLAMA_LOG_DEBUG(logger, ...)    logger.debugWrapper  (__VA_ARGS__);
    #define LLAMA_LOG_INFO(logger, ...)     logger.infoWrapper   (__VA_ARGS__);
    #define LLAMA_LOG_WARNING(logger, ...)  logger.warningWrapper(__VA_ARGS__);
    #define LLAMA_LOG_ERROR(logger, ...)    logger.errorWrapper  (__VA_ARGS__);
    #define LLAMA_LOG_ERROR_X(logger, ...)  logger.error_xWrapper(__VA_ARGS__);
#endif

namespace llama {
/**
 *  @brief Require the implemention of stream operator <<
 */
module_check(stream_operator, operator <<);

/**
 *  @brief Require the implemention of stream flush
 */
module_check(flush_stream, flush);

template <typename STREAM = std::ostream>
class LoggerWrapper {
 public:
    /**
     *  @brief Constructor for any object with operator<<
     *
     *  @param to Output fstream
     */
    template <typename = typename std::enable_if<
                                        module_check_stream_operator<STREAM, STREAM&>::value &&
                                        module_check_flush_stream<STREAM, STREAM&>::value>
                                  >
    explicit LoggerWrapper(STREAM& to, bool color = false) : _to(to), _color(color) {
    }

    /**
     *  @brief Constructor for std::ostream
     *
     *  @param to Output stream
     */
    explicit LoggerWrapper(std::ostream& to, bool color = true) : _to(to), _color(color) {
    }

    /**
     *  @brief Constructor for std::ofstream
     *
     *  @param to Output fstream
     */
    explicit LoggerWrapper(std::ofstream& to) : _to(to), _color(false) {
    }

    /**
     *  @brief Debug message wrapper
     */
    template <typename ... Arg>
    void debugWrapper(Arg&& ... args) {
#if (LLAMA_LOG_LEVEL <= LLAMA_LOG_LEVEL_DEBUG)
        std::lock_guard<std::mutex> locker(_stream_mtx);
        _to << "[DEBUG] ";
        debug(std::forward<Arg>(args)...);
        _to.flush();
#endif
    }

    /**
     *  @brief Info message wrapper
     */
    template <typename ... Arg>
    void infoWrapper(Arg&& ... args) {
#if (LLAMA_LOG_LEVEL <= LLAMA_LOG_LEVEL_INFO)
        std::lock_guard<std::mutex> locker(_stream_mtx);
        _to << "[INFO] ";
        info(std::forward<Arg>(args)...);
        _to.flush();
#endif
    }

    /**
     *  @brief Warning message wrapper
     */
    template <typename ... Arg>
    void warningWrapper(Arg&& ... args) {
#if (LLAMA_LOG_LEVEL <= LLAMA_LOG_LEVEL_DEBUG)
        std::lock_guard<std::mutex> locker(_stream_mtx);
        _to << "[WARNING] ";
        warning(std::forward<Arg>(args)...);
        _to.flush();
#endif
    }

    /**
     *  @brief Error message wrapper
     */
    template <typename ... Arg>
    void errorWrapper(Arg&& ... args) {
#if (LLAMA_LOG_LEVEL <= LLAMA_LOG_LEVEL_DEBUG)
        std::lock_guard<std::mutex> locker(_stream_mtx);
        if (_color) {
            _to << "[\e[0;31mERROR\e[0m] ";
        } else {
            _to << "[ERROR] ";
        }
        error(std::forward<Arg>(args)...);
        _to.flush();
#endif
    }

    /**
     *  @brief Error and exit message wrapper
     */
    template <typename ... Arg>
    void __attribute__((noreturn)) error_xWrapper(Arg&& ... args) {
#if (LLAMA_LOG_LEVEL <= LLAMA_LOG_LEVEL_DEBUG)
        std::lock_guard<std::mutex> locker(_stream_mtx);
        if (_color) {
            _to << "[\e[0;31mERROR\e[0m] ";
        } else {
            _to << "[ERROR] ";
        }
        error_x(std::forward<Arg>(args)...);
#endif
    }

 private:
    /**
     *  @brief Output stream
     */
    STREAM& _to;

    /**
     *  @brief Mutex for stream
     */
    std::mutex _stream_mtx;

    /**
     *  @brief Enable color
     */
    bool _color;

    /**
     *  @brief Disable copy constructor
     */
    LoggerWrapper(const LoggerWrapper& _) = delete;

    /**
     *  @brief Disable move constructor
     */
    LoggerWrapper(LoggerWrapper&& _) = delete;

    /**
     *  @brief Disable copy assignment constuctor
     */
    LoggerWrapper& operator= (const LoggerWrapper& _) = delete;

    /**
     *  @brief Disable move assignment constructor
     */
    LoggerWrapper& operator= (LoggerWrapper&& _) = delete;


    /**
     *  @brief Debug (base function)
     */
    void debug() {
    }

    /**
     *  @brief Debug (recursive variadic function)
     *
     *  @param t    Object to ostream at this time
     *  @param args Rest objects
     */
    template <typename T, typename ... Arg>
    void debug(T&& t, Arg&& ... args) {
        _to << std::forward<T>(t);
        debug(std::forward<Arg>(args)...);
    }

    /**
     *  @brief Info (base function)
     */
    void info() {
    }

    /**
     *  @brief Info (recursive variadic function)
     *
     *  @param t    Object to ostream at this time
     *  @param args Rest objects
     */
    template <typename T, typename ... Arg>
    void info(T&& t, Arg&& ... args) {
#if (LLAMA_LOG_LEVEL <= LLAMA_LOG_LEVEL_INFO)
        _to << std::forward<T>(t);
        info(std::forward<Arg>(args)...);
#endif
    }

    /**
     *  @brief Warning (base function)
     */
    void warning() {
    }

    /**
     *  @brief Warning (recursive variadic function)
     *
     *  @param t    Object to ostream at this time
     *  @param args Rest objects
     */
    template <typename T, typename ... Arg>
    void warning(T&& t, Arg&& ... args) {
#if (LLAMA_LOG_LEVEL <= LLAMA_LOG_LEVEL_WARNING)
        _to << std::forward<T>(t);
        warning(std::forward<Arg>(args)...);
#endif
    }

    /**
     *  @brief Error (base function)
     */
    void error() {
    }

    /**
     *  @brief Error (recursive variadic function)
     *
     *  @param t    Object to ostream at this time
     *  @param args Rest objects
     */
    template <typename T, typename ... Arg>
    void error(T&& t, Arg&& ... args) {
#if (LLAMA_LOG_LEVEL <= LLAMA_LOG_LEVEL_ERROR)
        _to << std::forward<T>(t);
        error(std::forward<Arg>(args)...);
#endif
    }

    /**
     *  @brief Error and exit
     *
     *  @param args Objects to ostream
     *
     *  @note  This function will call exit(EXIT_FAILURE)
     */
    template <typename ... Arg>
    void __attribute__((noreturn)) error_x(Arg&& ... args) {
#if (LLAMA_LOG_LEVEL <= LLAMA_LOG_LEVEL_ERROR_X)
        error(std::forward<Arg>(args)...);
#endif
        _to.flush();
        exit(EXIT_FAILURE);
    }
};
using Logger = LoggerWrapper<>;
}  // namespace llama

#endif  // LLAMA_CPP_SRC_UTILITY_LOGGER_H_
