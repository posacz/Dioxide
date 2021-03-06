
/**
 * @file XmlRpcSource.cc
 * @author Chris Morley
 */

#include "tier3/xmlrpcinterface/xmlrpc++/XmlRpcSource.h"
#include "tier3/xmlrpcinterface/xmlrpc++/XmlRpcSocket.h"
#include "tier3/xmlrpcinterface/xmlrpc++/XmlRpcUtil.h"

namespace XmlRpc {


  XmlRpcSource::XmlRpcSource(int fd /*= -1*/, bool deleteOnClose /*= false*/) 
    : _fd(fd), _deleteOnClose(deleteOnClose), _keepOpen(false)
  {
  }

  XmlRpcSource::~XmlRpcSource()
  {
  }


  void
  XmlRpcSource::close()
  {
    if (_fd != -1) {
      XmlRpcUtil::log(2,"XmlRpcSource::close: closing socket %d.", _fd);
      XmlRpcSocket::close(_fd);
      XmlRpcUtil::log(2,"XmlRpcSource::close: done closing socket %d.", _fd);
      _fd = -1;
    }
    if (_deleteOnClose) {
      XmlRpcUtil::log(2,"XmlRpcSource::close: deleting this");
      _deleteOnClose = false;
      delete this;
    }
#ifdef USE_SSL
    if (_ssl_ssl != (SSL *) NULL) {
      SSL_shutdown (_ssl_ssl);
      SSL_free (_ssl_ssl);
      SSL_CTX_free (_ssl_ctx);
    }
#endif
  }

} // namespace XmlRpc
