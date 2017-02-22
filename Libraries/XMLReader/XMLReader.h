#ifndef XMLREADER_H
#define XMLREADER_H

#include <Arduino.h>
#include <ESPAsyncTCP.h>

enum XML_Status
{
  XML_IDLE,
  XML_DONE,
  XML_COMPLETED,
  XML_TIMEOUT
};

struct XML_tag_t
{
  const char  *pszTag;
  const char  *pszAttr;
  const char  *pszValue;
  int16_t     valueCount;
};

class XMLReader
{
public:
  XMLReader(void (*xml_callback)(int item, int idx, char *p, char *pTag), const XML_tag_t *pTags);
  bool  begin(const char *pHost, int port, String path);

private:
  bool  combTag(const char *pTagName, const char *pAttr, const char *pValue);
  bool  nextValue(void);
  bool  fillBuffer(char* data, size_t len);
  void  emptyBuffer(void);
  void  sendHeader(const char *pHeaderName, const char *pHeaderValue);
  void  sendHeader(const char *pHeaderName, int nHeaderValue);
  bool  tagCompare(char *p1, const char *p2);
  void  IncPtr(void);
  bool  tagStart(void);
  int   tagCnt(void);
  bool  tagEnd(void);

  void  (*m_xml_callback)(int item, int idx, char *p, char *pTag);

  AsyncClient m_client;

  void _onConnect(AsyncClient* client);
  void _onDisconnect(AsyncClient* client);
  static void _onError(AsyncClient* client, int8_t error);
  void _onTimeout(AsyncClient* client, uint32_t time);
  void _onData(AsyncClient* client, char* data, size_t len);

  const char  *m_pHost;
  char m_buffer[512];
  String m_path;
  const XML_tag_t *m_pTags;
  char   *m_pPtr;
  char   *m_pEnd;
  char   *m_pIn;
  char   *m_pTag;
  const char *m_pTagName;
  bool   m_binValues;
  int m_tagIdx;
  int m_valIdx;
  int8_t m_tagState;
};

#endif // XMLREADER_H
