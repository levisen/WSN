
#include <contiki.h>
#include <stdio.h>
#include "cc2420.h"

PROCESS(channel_sensing, "channel_sensing");
AUTOSTART_PROCESSES(&channel_sensing);

#define RSSI_MEASURES 200

PROCESS_THREAD(channel_sensing, ev, data)
{
  static struct etimer timer;
  int channel_measures[16];
  int _cur_rssi;
  int _best_rssi_mean;
  uint8_t _best_chan = 0;

  PROCESS_BEGIN();

  etimer_set(&timer, CLOCK_SECOND * 20);
  cc2420_on();

  while (1)
  {
    _best_rssi_mean = 0.0;
    for (size_t i = 0; i < 16; i++)
    {
      cc2420_set_channel(i + 11);   
      _cur_rssi = 0;
      for(size_t j = 0; j < RSSI_MEASURES; j++){
        _cur_rssi =  _cur_rssi + cc2420_rssi();
      }
      channel_measures[i] = _cur_rssi / RSSI_MEASURES;

      printf("Channel %d mean RSSI %d dBm\n",i + 11,channel_measures[i]);
    }
    for(size_t i = 0; i < 16; i++){
      if(channel_measures[i] < _best_rssi_mean){
        _best_rssi_mean = channel_measures[i];
        _best_chan = i;
      }
    }
    printf("Using channel %d with lowest RSSI noice of %d \n",_best_chan,_best_rssi_mean);

    /* Wait for the periodic timer to expire and then restart the timer. */
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer));
    etimer_reset(&timer);
  }

  PROCESS_END();
}
