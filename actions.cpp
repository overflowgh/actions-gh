OnEventData(void* pData)

{
  ......

  //  pData is a void* pData, 

  //  EventData is a structure e.g. 
  //  typedef struct _EventData {
  //  std::string id;
  //  std:: string remote_id;
  //  } EventData;

  // On Some Situation a void pointer *pData
  // has been static_casted as 
  // EventData* pointer 

  EventData *evtdata = static_cast<EventData*>(pData);
  .....
}
