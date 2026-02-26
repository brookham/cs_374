#include "ppm.h"
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

struct thread_args {
  struct ppm *img_info;
  int thread_id;
  int start_y;
  int slice_h;
  long long sum_r;
  long long sum_g;
  long long sum_b;
};

void *run(void *arg)
{
  struct thread_args *args = (struct thread_args *)arg;
  int width = args->img_info->width;
  int end_y = args->start_y + args->slice_h;

  printf("Thread %d: %d %d\n", args->thread_id, args->start_y, args->slice_h);

  for (int y = args->start_y; y < end_y; y++) {
    for (int x = 0; x < width; x++) {
      int pixel = ppm_get_pixel(args->img_info, x, y);
      int r = PPM_PIXEL_R(pixel);
      int g = PPM_PIXEL_G(pixel);
      int b = PPM_PIXEL_B(pixel);

      args->sum_r += r;
      args->sum_g += g;
      args->sum_b += b;

      int gray = (299 * r + 587 * g + 114 * b) / 1000;
      int gray_pixel = PPM_PIXEL(gray, gray, gray);
      ppm_set_pixel(args->img_info, x, y, gray_pixel);
    }
  }

  return NULL;
}

int main(int argc, char *argv[])
{
  if (argc < 3){
    printf("Usage: %s <num_threads> <input.ppm> <output.ppm>\n", argv[0]);
  }

  struct ppm *img_info = ppm_read(argv[2]);

  int num_threads = atoi(argv[1]);
  pthread_t thread[num_threads];


  struct thread_args args[num_threads];

  int base = img_info->height / num_threads;
  int rem = img_info->height % num_threads;

  for (int i = 0; i < num_threads; i++) {
    args[i].img_info = img_info;
    args[i].thread_id = i;
    args[i].start_y = i * base;
    args[i].slice_h = base + ((i == num_threads - 1) ? rem : 0);
    args[i].sum_r = 0;
    args[i].sum_g = 0;
    args[i].sum_b = 0;

    pthread_create(&thread[i], NULL, run, &args[i]);
  }

  long long total_r = 0;
  long long total_g = 0;
  long long total_b = 0;

  for (int i = 0; i < num_threads; i++) {
    pthread_join(thread[i], NULL);
    total_r += args[i].sum_r;
    total_g += args[i].sum_g;
    total_b += args[i].sum_b;
  }

  long long total_pixels = (long long)img_info->width * img_info->height;
  int avg_r = (int)(total_r / total_pixels);
  int avg_g = (int)(total_g / total_pixels);
  int avg_b = (int)(total_b / total_pixels);

  printf("Average R: %d\n", avg_r);
  printf("Average G: %d\n", avg_g);
  printf("Average B: %d\n", avg_b);

  ppm_write(img_info, argv[3]);
  ppm_free(img_info);

  return 0;
}