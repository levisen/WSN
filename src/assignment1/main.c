
#include <contiki.h>
#include <math.h>
#include "DTC.c"




PROCESS(signal_compression_process, "signal_compression");
AUTOSTART_PROCESSES(&signal_compression_process);

PROCESS_THREAD(signal_compression_process, ev, data)
{
  static struct etimer timer;
  // Define H
  double H[DTC_L][DTC_L];
  double invH[DTC_L][DTC_L];
  generateDTCMatrix(H);
  //display(H);


  // Generate signal x
  double x[DTC_N];
  // for (size_t i = 0; i < DTC_N; i++)
  // {
  //   x[i] = sin((double)i / 100);
  // }
  x[0] = 0.35;
  x[1] = 0.35;
  x[2] = 0.35;
  x[3] = 0.35;
  x[4] = 0.35;
  x[5] = 0.35;
  x[6] = 0.35;
  x[7] = 0.35;
  x[8] = 0.35;
  x[9] = 0.02;
  x[10] = -0.21;
  x[11] = -0.33;
  x[12] = -0.37;
  x[13] = -0.335;
  x[14] = -0.285;
  x[15] = -0.23;
  printf("Original\n");
  for (size_t i = 0; i < DTC_N; i++)
  {
    printf("%f ",x[i]);
  }
  printf("\n");


  // DCT transform of signal x

  // Start nulling all values
  double y[DTC_N/DTC_L][DTC_L];
  for(int i = 0; i < DTC_N/DTC_L; i++){
    for(int j = 0; j < DTC_L; j++){
      y[i][j] = 0.0;
    }
  }

  // Calculate Y
  int start_range = 0, end_range = 0, k = 0;
  double tmpCalc;
  for(int batch = 1; batch < (DTC_N/DTC_L) + 1; batch++){
    // Run through each batch
    start_range = DTC_L * ( batch - 1 );
    end_range = (DTC_L * batch) - 1;
    // Process each signal in y
    for(int i = 0; i < DTC_L; i++){
      //printf("H %f\n",H[i][0]);
      k = 0;
      tmpCalc = 0;
      for(int j = start_range; j < end_range + 1; j++){
        tmpCalc = tmpCalc + ( x[j] * H[i][k] );
        //printf("i: %d, k: %d, H[i][k]: %f * x[j]:%f, j:%d \n",i,k,H[i][k],x[j],j);
        k++;
      }
      y[batch - 1][i] = tmpCalc;
    }
  }
  //display(y);
  // move to y transmit
  double y_t[DTC_N/DTC_L][DTC_M];
  for(int i = 0; i < DTC_N/DTC_L; i++){
    for(int j = 0; j < DTC_M; j++){
      y_t[i][j] = y[i][j];
    }
  }


  // reconstruct
  double y_r[DTC_N/DTC_L][DTC_L];
  for(int i = 0; i < DTC_N/DTC_L; i++){
    for(int j = 0; j < DTC_L; j++){
      if(j > DTC_M - 1){
        y_r[i][j] = 0.0;
      } else {
        y_r[i][j] = y_t[i][j];
        
      }
      //printf("%f ",y_r[i][j]);
    }
    //printf("\n");   
  }
  
  
  generateInverseMatrix(H,invH);
  double x_rec[DTC_N];
  int x_index = 0;
  // For each batch
  for(int i = 0; i < DTC_N/DTC_L; i++)
  {
    //printf("new batch\n");
    // For each signal
    for(int j = 0; j < DTC_L; j++){
      for(int k = 0; k < DTC_L; k++){
        //printf("inv %f  y_rec %f\n",invH[j][k],y_r[i][k]);
        x_rec[x_index] += ( invH[j][k] * y_r[i][k] );
      }
      x_index += 1;
      //printf("tmp %f \n",tmp);
    }
  }

  // Print reconstructed signal
  printf("Reconstructed: \n");
  for (size_t i = 0; i < DTC_N; i++)
  {
      printf("%f ",x_rec[i]);
  }
  printf("\n");
  // display(invH);

  PROCESS_BEGIN();
  /* Setup a periodic timer that expires after 10 seconds. */
  etimer_set(&timer, CLOCK_SECOND * 10);

  while (1)
  {

    /* Wait for the periodic timer to expire and then restart the timer. */
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer));
    etimer_reset(&timer);
  }

  PROCESS_END();
}
