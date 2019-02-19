// #define DEMO_USING_SSL
// #define BOOST_ASIO_ENABLE_HANDLER_TRACKING

#include "HttpHandler.h"
#include <boost/bind.hpp>  
#include "http_mark.h"

HttpHandler::HttpHandler(boost::asio::io_service& io_service/*, boost::asio::ssl::context& context*/)
: resolver_(io_service), socket_(io_service
#ifdef DEMO_USING_SSL
 , context) {
	socket_.set_verify_mode(boost::asio::ssl::verify_peer);
	socket_.set_verify_callback(
		boost::bind(&HttpHandler::verify_certificate, this, _1, _2));
#else
)
{
	/*(void)context;*/
#endif
}

HttpHandler::~HttpHandler(){
}

// bool HttpHandler::verify_certificate(bool preverified,
// 	boost::asio::ssl::verify_context& ctx)
// {
// 	// The verify callback can be used to check whether the certificate that is
// 	// being presented is valid for the peer. For example, RFC 2818 describes
// 	// the steps involved in doing this for HTTPS. Consult the OpenSSL
// 	// documentation for more details. Note that the callback is called once
// 	// for each certificate in the certificate chain, starting from the root
// 	// certificate authority.
// 
// 	// In this example we will simply print the certificate's subject name.
// 	char subject_name[256];
// 	X509* cert = X509_STORE_CTX_get_current_cert(ctx.native_handle());
// 	X509_NAME_oneline(X509_get_subject_name(cert), subject_name, 256);
// 	std::cout << "Verifying " << subject_name << "\n";
// 
// 	return preverified;
// }

int HttpHandler::post(const std::string& url) {
	handle_request_resolve(url, HttpBase::buildPostRequest);
	return HTTP_SUCCESS;
}

int HttpHandler::get(const std::string& url) {
	handle_request_resolve(url, HttpBase::buildGetRequest);
	return HTTP_SUCCESS;
}

void HttpHandler::handle_request_resolve(const std::string& url, pBuildRequest func) {
	try {
		responseData_.clear();
		// ����URL  
		std::string server, port, path;
		parseUrl(url, server, port, path);

		std::ostream request_stream(&request_);

		// �ϳ�����  
		func(server, path, request_stream);

		// ���������ַ\�˿�  
		boost::asio::ip::tcp::resolver::query query(server, port);
		resolver_.async_resolve(query,
			boost::bind(&HttpHandler::handle_resolve, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::iterator));
	}
	catch (std::exception& e) {
#ifdef DEMO_USING_SSL
		socket_.shutdown();
#else
		socket_.close();
#endif
		std::cout << "Exception: " << e.what() << "\n";
	}
	return;
}

void HttpHandler::handle_resolve(const boost::system::error_code& err,
	boost::asio::ip::tcp::resolver::iterator endpoint_iterator) {
	if (err) {
		std::cout << "Error: " << err << "\n";
		return;
	}

	// ��������  
	boost::asio::async_connect(socket_, endpoint_iterator,
		boost::bind(&HttpHandler::handle_connect, this,
		boost::asio::placeholders::error));
}

void HttpHandler::handle_connect(const boost::system::error_code& err) {
	if (err) {
		std::cout << "Error: " << err << "\n";
		return;
	}

	// ����request����  
	boost::asio::async_write(socket_, request_,
		boost::bind(&HttpHandler::handle_write_request, this,
		boost::asio::placeholders::error));
}

void HttpHandler::handle_write_request(const boost::system::error_code& err) {
	if (err) {
		std::cout << "Error: " << err << "\n";
		return;
	}

	// �첽���������ݵ�response_��ֱ������Э����� \r\n Ϊֹ  
	boost::asio::async_read_until(socket_, response_, "\r\n",
		boost::bind(&HttpHandler::handle_read_status_line, this,
		boost::asio::placeholders::error));
}

void HttpHandler::handle_read_status_line(const boost::system::error_code& err) {
	if (err) {
		std::cout << "Error: " << err << "\n";
		return;
	}

	// ����buff  
	std::istream response_stream(&response_);
	unsigned int status_code;
	std::string http_version, status_message;
	response_stream >> http_version;
	response_stream >> status_code;
	std::getline(response_stream, status_message);

	// �˶��Ƿ�����ȷ����  
	if (!response_stream || http_version.substr(0, 5) != "HTTP/") {
		std::cout << "�������Ӧ����\n";
		return;
	}
	if (status_code != 200) {
		std::cout << "��������Ӧ��״̬��: " << status_code << "\n";
		return;
	}

	// ��ȡ��Ӧͷ,ֱ������Э����� \r\n\r\n Ϊֹ  
	boost::asio::async_read_until(socket_, response_, "\r\n\r\n",
		boost::bind(&HttpHandler::handle_read_headers, this,
		boost::asio::placeholders::error));
}

void HttpHandler::handle_read_headers(const boost::system::error_code& err) {
	if (err) {
		std::cout << "Error: " << err << "\n";
		return;
	}
	// �����Ӧͷ  
	std::istream response_stream(&response_);
	std::string header;
	while (std::getline(response_stream, header) && header != "\r") {
#ifdef _DEBUG  
		std::cout << header << "\n";
#endif   
	}
#ifdef _DEBUG  
	std::cout << "\n";
#endif   

	// д������ʣ�������  
	if (response_.size() > 0) {
		boost::asio::streambuf::const_buffers_type cbt = response_.data();
		responseData_ += std::string(boost::asio::buffers_begin(cbt), boost::asio::buffers_end(cbt));
#ifdef _DEBUG  
		std::cout << &response_;
#endif   
	}

	// ��ʼ��ȡʣ����������  
	boost::asio::async_read(socket_, response_,
		boost::asio::transfer_at_least(1),
		boost::bind(&HttpHandler::handle_read_content, this,
		boost::asio::placeholders::error));
}

void HttpHandler::handle_read_content(const boost::system::error_code& err) {
	if (!err) {
		// �������������  
		boost::asio::streambuf::const_buffers_type cbt = response_.data();
		responseData_ += std::string(boost::asio::buffers_begin(cbt), boost::asio::buffers_end(cbt));
#ifdef _DEBUG  
		std::cout << &response_;
#endif   

		// ������ȡʣ�����ݣ�ֱ������EOF  
		boost::asio::async_read(socket_, response_,
			boost::asio::transfer_at_least(1),
			boost::bind(&HttpHandler::handle_read_content, this,
			boost::asio::placeholders::error));
	}
	else if (err != boost::asio::error::eof) {
		std::cout << "Error: " << err << "\n";
	}
	else {
#ifdef DEMO_USING_SSL
		socket_.shutdown();
#else
		socket_.close();
#endif
		resolver_.cancel();

		std::cout << "��ȡ��Ӧ�������." << std::endl;
	}
}


std::string post(std::string url) {
	boost::asio::io_service io;
// 	boost::asio::ssl::context ctx(boost::asio::ssl::context::sslv23);
// 	ctx.set_default_verify_paths();
	HttpHandler c(io);
	c.post(url);
	io.run();
	return c.getResponse();
}

std::string get(std::string url) {
	boost::asio::io_service io;
// 	boost::asio::ssl::context ctx(boost::asio::ssl::context::sslv23);
// 	ctx.set_default_verify_paths();
	HttpHandler c(io);
	c.get(url);
	io.run();
	return c.getResponse();
}