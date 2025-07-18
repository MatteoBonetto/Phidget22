#ifndef _LCD_H_
#define _LCD_H_
typedef struct _PhidgetLCD *PhidgetLCDHandle;

/* Methods */
API_PRETURN_HDR PhidgetLCD_create(PhidgetLCDHandle *ch);
API_PRETURN_HDR PhidgetLCD_delete(PhidgetLCDHandle *ch);
API_PRETURN_HDR PhidgetLCD_setCharacterBitmap(PhidgetLCDHandle ch, PhidgetLCD_Font font,
  const char *character, const uint8_t *bitmap);
API_VRETURN_HDR PhidgetLCD_setCharacterBitmap_async(PhidgetLCDHandle ch, PhidgetLCD_Font font,
  const char *character, const uint8_t *bitmap, Phidget_AsyncCallback fptr, void *ctx);
API_PRETURN_HDR PhidgetLCD_getMaxCharacters(PhidgetLCDHandle ch, PhidgetLCD_Font font,
  int *maxCharacters);
API_PRETURN_HDR PhidgetLCD_clear(PhidgetLCDHandle ch);
API_VRETURN_HDR PhidgetLCD_clear_async(PhidgetLCDHandle ch, Phidget_AsyncCallback fptr, void *ctx);
API_PRETURN_HDR PhidgetLCD_copy(PhidgetLCDHandle ch, int sourceFramebuffer, int destFramebuffer,
  int sourceX1, int sourceY1, int sourceX2, int sourceY2, int destX, int destY, int inverted);
API_VRETURN_HDR PhidgetLCD_copy_async(PhidgetLCDHandle ch, int sourceFramebuffer, int destFramebuffer,
  int sourceX1, int sourceY1, int sourceX2, int sourceY2, int destX, int destY, int inverted, Phidget_AsyncCallback fptr, void *ctx);
API_PRETURN_HDR PhidgetLCD_drawLine(PhidgetLCDHandle ch, int x1, int y1, int x2, int y2);
API_VRETURN_HDR PhidgetLCD_drawLine_async(PhidgetLCDHandle ch, int x1, int y1, int x2, int y2,
  Phidget_AsyncCallback fptr, void *ctx);
API_PRETURN_HDR PhidgetLCD_drawPixel(PhidgetLCDHandle ch, int x, int y,
  PhidgetLCD_PixelState pixelState);
API_VRETURN_HDR PhidgetLCD_drawPixel_async(PhidgetLCDHandle ch, int x, int y,
  PhidgetLCD_PixelState pixelState, Phidget_AsyncCallback fptr, void *ctx);
API_PRETURN_HDR PhidgetLCD_drawRect(PhidgetLCDHandle ch, int x1, int y1, int x2, int y2, int filled,
  int inverted);
API_VRETURN_HDR PhidgetLCD_drawRect_async(PhidgetLCDHandle ch, int x1, int y1, int x2, int y2, int filled,
  int inverted, Phidget_AsyncCallback fptr, void *ctx);
API_PRETURN_HDR PhidgetLCD_flush(PhidgetLCDHandle ch);
API_VRETURN_HDR PhidgetLCD_flush_async(PhidgetLCDHandle ch, Phidget_AsyncCallback fptr, void *ctx);
API_PRETURN_HDR PhidgetLCD_getFontSize(PhidgetLCDHandle ch, PhidgetLCD_Font font, int *width,
  int *height);
API_PRETURN_HDR PhidgetLCD_setFontSize(PhidgetLCDHandle ch, PhidgetLCD_Font font, int width,
  int height);
API_PRETURN_HDR PhidgetLCD_initialize(PhidgetLCDHandle ch);
API_PRETURN_HDR PhidgetLCD_saveFrameBuffer(PhidgetLCDHandle ch, int frameBuffer);
API_VRETURN_HDR PhidgetLCD_saveFrameBuffer_async(PhidgetLCDHandle ch, int frameBuffer,
  Phidget_AsyncCallback fptr, void *ctx);
API_PRETURN_HDR PhidgetLCD_writeBitmap(PhidgetLCDHandle ch, int xPosition, int yPosition, int xSize,
  int ySize, const uint8_t *bitmap);
API_VRETURN_HDR PhidgetLCD_writeBitmap_async(PhidgetLCDHandle ch, int xPosition, int yPosition, int xSize,
  int ySize, const uint8_t *bitmap, Phidget_AsyncCallback fptr, void *ctx);
API_PRETURN_HDR PhidgetLCD_writeText(PhidgetLCDHandle ch, PhidgetLCD_Font font, int xPosition,
  int yPosition, const char *text);
API_VRETURN_HDR PhidgetLCD_writeText_async(PhidgetLCDHandle ch, PhidgetLCD_Font font, int xPosition,
  int yPosition, const char *text, Phidget_AsyncCallback fptr, void *ctx);

/* Properties */
API_PRETURN_HDR PhidgetLCD_setAutoFlush(PhidgetLCDHandle ch, int autoFlush);
API_PRETURN_HDR PhidgetLCD_getAutoFlush(PhidgetLCDHandle ch, int *autoFlush);
API_PRETURN_HDR PhidgetLCD_setBacklight(PhidgetLCDHandle ch, double backlight);
API_PRETURN_HDR PhidgetLCD_getBacklight(PhidgetLCDHandle ch, double *backlight);
API_PRETURN_HDR PhidgetLCD_getMinBacklight(PhidgetLCDHandle ch, double *minBacklight);
API_PRETURN_HDR PhidgetLCD_getMaxBacklight(PhidgetLCDHandle ch, double *maxBacklight);
API_PRETURN_HDR PhidgetLCD_setContrast(PhidgetLCDHandle ch, double contrast);
API_PRETURN_HDR PhidgetLCD_getContrast(PhidgetLCDHandle ch, double *contrast);
API_PRETURN_HDR PhidgetLCD_getMinContrast(PhidgetLCDHandle ch, double *minContrast);
API_PRETURN_HDR PhidgetLCD_getMaxContrast(PhidgetLCDHandle ch, double *maxContrast);
API_PRETURN_HDR PhidgetLCD_setCursorBlink(PhidgetLCDHandle ch, int cursorBlink);
API_PRETURN_HDR PhidgetLCD_getCursorBlink(PhidgetLCDHandle ch, int *cursorBlink);
API_PRETURN_HDR PhidgetLCD_setCursorOn(PhidgetLCDHandle ch, int cursorOn);
API_PRETURN_HDR PhidgetLCD_getCursorOn(PhidgetLCDHandle ch, int *cursorOn);
API_PRETURN_HDR PhidgetLCD_setFrameBuffer(PhidgetLCDHandle ch, int frameBuffer);
API_VRETURN_HDR PhidgetLCD_setFrameBuffer_async(PhidgetLCDHandle ch, int frameBuffer,
  Phidget_AsyncCallback fptr, void *ctx);
API_PRETURN_HDR PhidgetLCD_getFrameBuffer(PhidgetLCDHandle ch, int *frameBuffer);
API_PRETURN_HDR PhidgetLCD_getHeight(PhidgetLCDHandle ch, int *height);
API_PRETURN_HDR PhidgetLCD_setScreenSize(PhidgetLCDHandle ch, PhidgetLCD_ScreenSize screenSize);
API_PRETURN_HDR PhidgetLCD_getScreenSize(PhidgetLCDHandle ch, PhidgetLCD_ScreenSize *screenSize);
API_PRETURN_HDR PhidgetLCD_setSleeping(PhidgetLCDHandle ch, int sleeping);
API_PRETURN_HDR PhidgetLCD_getSleeping(PhidgetLCDHandle ch, int *sleeping);
API_PRETURN_HDR PhidgetLCD_getWidth(PhidgetLCDHandle ch, int *width);

/* Events */

#endif /* _LCD_H_ */
