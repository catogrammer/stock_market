#include <spdlog/spdlog.h>
#include <spdlog/async.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace spdlog_w
{
    using namespace spdlog;

    void init_async()
    {
        init_thread_pool( 8192, 2 ); // Queue size 8192 and 2 background threads
        auto async_console_logger = spdlog::create_async<spdlog::sinks::stdout_color_sink_mt>( "async_console" );
        set_default_logger( async_console_logger );
        info( "Asynchronous logging initialized" );
    }
}
