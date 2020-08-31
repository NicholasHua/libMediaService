#include "mk_client_connection.h"
#include "mk_media_common.h"

mk_client_connection::mk_client_connection()
{
    m_ulIndex        = 0;
    m_enType         = MK_CLIENT_TYPE_MAX;
    m_enStatus       = MR_CLIENT_STATUS_MAX;
    m_recvBuf        = NULL;
    m_ulRecvBufLen   = 0;
    m_ulRecvLen      = 0;
    m_MediaCallBack  = NULL;
    m_pMediaCbData   = NULL;
    m_StatusCallBack = NULL;
    m_pStatusCbData  = NULL;
}
mk_client_connection::~mk_client_connection()
{

}
MK_CLIENT_TYPE mk_client_connection::client_type()
{
    return m_enType;
}
MR_CLIENT_STATUS mk_client_connection::get_status()
{
    return m_enStatus;
}
void  mk_client_connection::set_status_callback(handle_client_status cb,void* ctx)
{
    m_StatusCallBack = cb;
    m_pStatusCbData  = ctx;
}
int32_t  mk_client_connection::do_next_recv(char* buf,uint32_t len,handle_client_media cb,void* data)
{
    m_recvBuf        = buf;
    m_ulRecvBufLen   = len;
    m_ulRecvLen      = 0;
    m_MediaCallBack  = cb;
    m_pMediaCbData   = data;
    return recv_next();
}
void     mk_client_connection::set_index(uint32_t ulIdx)
{
    m_ulIndex = ulIdx;
}
uint32_t mk_client_connection::get_index()
{
    return m_ulIndex;
}
void    mk_client_connection::handle_connection_media(MR_MEDIA_TYPE enType,uint32_t pts)
{
    if(NULL == m_MediaCallBack) {
        return;
    }
    if(0 == m_ulRecvLen) {
        return;
    }
    m_MediaCallBack(this,enType,pts,m_recvBuf,m_ulRecvLen,m_pMediaCbData);
}
void    mk_client_connection::handle_connection_status(MR_CLIENT_STATUS  enStatus)
{
    m_enStatus = enStatus;
    if(NULL == m_StatusCallBack) {
        return;
    }
    m_StatusCallBack(this,m_enStatus,m_pStatusCbData);
}