#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

/*GPIO physical address and controlller*/
#define BCM2708_PERI_BASE 0x20000000
#define GPIO_BASE  (BCM2708_PERI_BASE+0x200000)


#define PAGE_SIZE (4*1024)
#define BLOCK_SIZE (4*1024)


#define INP_GPIO(g) *(gpio+((g)/10)) &= ~(7<<(((g)%10)*3))
#define OUT_GPIO(g) *(gpio+((g)/10)) |=  (1<<(((g)%10)*3))
#define SET_GPIO_ALT(g,a) *(gpio+(((g)/10))) |= (((a)<=3?(a)+4:(a)==4?3:2)<<(((g)%10)*3))

#define GPIO_SET *(gpio+7)
#define GPIO_CLR *(gpio+10)




/*I/O access*/
int mem_fd;
void *gpio_map;
volatile unsigned *gpio;


void setup_io();


void setup_io()
{
  /*open /dev/mem*/
 
  if((mem_fd = open("/dev/mem", O_RDWR | O_SYNC)) < 0)
   {
     printf("Can't open /dev/mem \n");
     return -1;
   }
   
  /*mamp GPIO*/
  gpio_map = mmap(NULL, BLOCK_SIZE, PROT_READ|PROT_WRITE,MAP_SHARED, mem_fd, GPIO_BASE);
  close(mem_fd);
  if(gpio_map == MAP_FAILED)
  {
   printf("mmap error %d \n", (int)gpio_map);
   exit(-1);
  }
  gpio = (volatile unsigned *) gpio_map;
}

int main()
{

int g,rep;
setup_io(); /*Direct Register access*/

#if 0
/*Set gpio 7..11 to outpu mode*/
for(g=7; g <= 18; g++)
{
 INP_GPIO(g);
 OUT_GPIO(g);

} 
#endif

INP_GPIO(17);
OUT_GPIO(17);

while(1)
{
 GPIO_SET = 1 << 17;
 //delay(500);
 sleep(1);
 GPIO_CLR = 1 << 17;
 //delay(500);
 sleep(1);

}

#if 0
for (rep=0; rep=10; rep++)
{  
  for(g=7; g <= 11; g++)
   {
      GPIO_SET = 1 << g;
      sleep(1);
   }
  for(g=7; g<= 11; g++)
  {
      GPIO_CLR = 1 << g;
      sleep(1); 
  } 
}


#endif

}

