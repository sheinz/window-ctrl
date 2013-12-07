#ifndef __CWINDOW_H__
#define __CWINDOW_H__

#include <inttypes.h>
#include "CTaskMgr.h"
#include "AFMotor.h"


class CWindow : public ITask
{
public:
   static CWindow* instance();

   virtual void init(void);
   virtual void onExecute(void);


   void calibrate(void);

   void open(void);
   void close(void);

   void set(uint8_t open_percent);
   uint8_t get();

   bool is_calibrating(void);

   bool is_idle(void);

   bool is_locked(void);

   uint32_t get_calib(void);

private:
   CWindow(void);

   AF_DCMotor m_motor;

   // time of full open/close in ms
   uint32_t m_full_ms;

   // time to stop the operation
   uint32_t m_op_time_stop;

   // Percentage of how wide window is currently open
   uint8_t m_curr_percentage;

   // pending
   uint8_t m_pending_percentage;


   enum EState
   {
      IDLE = 0,
      CALIB_INIT_CLOSE,
      CALIB_FULL_OPEN,
      CALIB_FULL_CLOSE,
      CALIB_ERROR,
      INIT_CLOSE,
      OPEN,
      CLOSE,
   };

   EState m_state;

   void start_open();
   void start_close();
};


#endif  // __CWINDOW_H__
