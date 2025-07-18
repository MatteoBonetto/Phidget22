#ifndef _DICTIONARY_H_
#define _DICTIONARY_H_
typedef struct _PhidgetDictionary *PhidgetDictionaryHandle;

/* Methods */
#ifdef INCLUDE_PRIVATE
API_PRETURN_HDR PhidgetDictionary_enableControlDictionary(void);
#endif
#ifdef INCLUDE_PRIVATE
API_PRETURN_HDR PhidgetDictionary_addDictionary(int deviceSerialNumber, const char *label);
#endif
#ifdef INCLUDE_PRIVATE
API_PRETURN_HDR PhidgetDictionary_removeDictionary(int deviceSerialNumber);
#endif
#ifdef INCLUDE_PRIVATE
API_PRETURN_HDR PhidgetDictionary_loadDictionary(int dictionarySerialNumber, const char *file);
#endif
#ifdef INCLUDE_PRIVATE
API_PRETURN_HDR PhidgetDictionary_enableStatsDictionary(void);
#endif
API_PRETURN_HDR PhidgetDictionary_create(PhidgetDictionaryHandle *ch);
API_PRETURN_HDR PhidgetDictionary_delete(PhidgetDictionaryHandle *ch);
API_PRETURN_HDR PhidgetDictionary_add(PhidgetDictionaryHandle ch, const char *key, const char *value);
API_PRETURN_HDR PhidgetDictionary_removeAll(PhidgetDictionaryHandle ch);
API_PRETURN_HDR PhidgetDictionary_get(PhidgetDictionaryHandle ch, const char *key, char *value,
  size_t valueLen);
API_PRETURN_HDR PhidgetDictionary_remove(PhidgetDictionaryHandle ch, const char *key);
API_PRETURN_HDR PhidgetDictionary_scan(PhidgetDictionaryHandle ch, const char *start, char *keyList,
  size_t keyListLen);
API_PRETURN_HDR PhidgetDictionary_set(PhidgetDictionaryHandle ch, const char *key, const char *value);
API_PRETURN_HDR PhidgetDictionary_update(PhidgetDictionaryHandle ch, const char *key,
  const char *value);

/* Properties */

/* Events */
typedef void (CCONV *PhidgetDictionary_OnAddCallback)(PhidgetDictionaryHandle ch, void *ctx,
  const char *key, const char *value);

API_PRETURN_HDR PhidgetDictionary_setOnAddHandler(PhidgetDictionaryHandle ch,
  PhidgetDictionary_OnAddCallback fptr, void *ctx);
typedef void (CCONV *PhidgetDictionary_OnRemoveCallback)(PhidgetDictionaryHandle ch, void *ctx,
  const char *key);

API_PRETURN_HDR PhidgetDictionary_setOnRemoveHandler(PhidgetDictionaryHandle ch,
  PhidgetDictionary_OnRemoveCallback fptr, void *ctx);
typedef void (CCONV *PhidgetDictionary_OnUpdateCallback)(PhidgetDictionaryHandle ch, void *ctx,
  const char *key, const char *value);

API_PRETURN_HDR PhidgetDictionary_setOnUpdateHandler(PhidgetDictionaryHandle ch,
  PhidgetDictionary_OnUpdateCallback fptr, void *ctx);

#endif /* _DICTIONARY_H_ */
