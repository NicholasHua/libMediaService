#include "mk_rtmp_connection.h"



mk_rtmp_connection::mk_rtmp_connection()
{
    m_rtmpHandle = NULL;
}
mk_rtmp_connection::~mk_rtmp_connection()
{

}
int32_t mk_rtmp_connection::open(const char* pszUrl)
{
    return AS_ERROR_CODE_OK;
}
void    mk_rtmp_connection::close()
{
    return;
}