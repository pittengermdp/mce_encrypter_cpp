#include <iostream>
#include <boost/asio.hpp>
#include "MCEClientAuth.h"
#include <array>

using boost::asio::ip::tcp;



std::array<char, 16> issue_authentication_challenge(uint32_t session_id, uint32_t vendor_id, uint32_t product_id) {
    std::array<char, 16> encrypted_buff;
    initEncryption();
    int foo = encryptLogonAuth(
        session_id,
        vendor_id,
        product_id,
        0,
        encrypted_buff.data()
        );
    return encrypted_buff;
}


uint32_t bytes_to_uint32(const std::array<uint8_t, 13>& buffer, size_t start, bool little_endian) {
    if (little_endian) {
        // Convert from little endian
        return (buffer[start + 3] << 24) | (buffer[start + 2] << 16) | (buffer[start + 1] << 8) | buffer[start];
    }
    else {
        // Convert from big endian
        return (buffer[start] << 24) | (buffer[start + 1] << 16) | (buffer[start + 2] << 8) | buffer[start + 3];
    }
}

int main() {
    try {
        boost::system::error_code ec;
        boost::asio::io_service io_service;
        uint32_t session_id, vendor_id, product_id;


        // Listen on TCP port 1234
        tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 3460));
        std::array<uint8_t, 13> input_buffer;
    

        while (true) {
            // Create a new socket for each connection
            tcp::socket socket(io_service);
            acceptor.accept(socket);

            std::size_t n = boost::asio::read(
                socket, boost::asio::buffer(input_buffer),
                boost::asio::transfer_exactly(13), ec);
            //little endian
            if (input_buffer[0] == 0) {
                session_id =  bytes_to_uint32(input_buffer, 1, true);
                vendor_id   = bytes_to_uint32(input_buffer, 5, true);
                product_id = bytes_to_uint32(input_buffer, 9, true);
            }
            //Big Endian
            else {
                 session_id = bytes_to_uint32(input_buffer, 1, true);
                 vendor_id = bytes_to_uint32(input_buffer, 5, true);
                 product_id = bytes_to_uint32(input_buffer, 9, true);
            }

            // Process the data
            std::array<char, 16> encrypted_data = issue_authentication_challenge(session_id, vendor_id, product_id);

            // Send the response back
            std::size_t bytes_sent = boost::asio::write(socket, boost::asio::buffer(encrypted_data), ec);

            // Socket will be automatically closed when it goes out of scope here
        }
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}

