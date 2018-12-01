#pragma once
/*
使用ASIO POST 利用io_service 的线程安全，回到循环中去收发数据

steady_timer cancel 会触发一次错误回调
close 同理也会触发未完成的读写回调
重写网络库


asio::read write async_read async_write 确保收发数量
*/
