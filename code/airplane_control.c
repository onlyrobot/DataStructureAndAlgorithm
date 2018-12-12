#include <stdio.h>
#include <stdlib.h>
typedef struct runway
{
	int total_time;
	int remain_time;
} runway;
int main()
{
	int runway_num, land_time, takeoff_time;
	scanf("%d %d %d", &runway_num, &land_time, &takeoff_time);
	runway * r = (runway *)malloc(runway_num * sizeof(runway));
	for (int i = 0; i < runway_num; ++i) r[i].total_time = 0, r[i].remain_time = 0;
	int total_time = 0, total_land = 0, total_takeoff = 0, land_num, takeoff_num, \
		land_wait = 0, takeoff_wait = 0;

	scanf("%d %d", &land_num, &takeoff_num);
	int land_que = land_num, takeoff_que = takeoff_num;
	
	int close = 0, finished = 0;
	while (land_que > 0 || takeoff_que > 0 || !finished)
	{
		printf("Current Time: %4d\n", total_time); //time
		finished = 1;
		for (int i = 0; i < runway_num; ++i) //runways to be free
		{
			if (r[i].remain_time == 1)
			{
				r[i].remain_time = 0;
				printf("runway %02d is free\n", i + 1);
			}
			else if (r[i].remain_time > 1) --r[i].remain_time, finished = 0;
		}
		for (int i = 0; i < runway_num; ++i) //airplane to land or takeoff
		{
			if (r[i].remain_time == 0)
			{
				if (land_que > 0)
				{
					printf("airplane %04d is ready to land on runway %02d\n", 5000 + total_land + 1, i + 1);
					++total_land, --land_que, r[i].total_time += land_time, r[i].remain_time = land_time;
					finished = 0;
				}
				else if (takeoff_que > 0)
				{
					printf("airplane %04d is ready to takeoff on runway %02d\n", total_takeoff + 1, i + 1);
					++total_takeoff, --takeoff_que, r[i].total_time += takeoff_time, r[i].remain_time = takeoff_time;
					finished = 0;
				}
			}
		}
		//calculating the waiting time
		land_wait += land_que, takeoff_wait += takeoff_que;
		if (!close)
		{
			scanf("%d %d", &land_num, &takeoff_num);
			if (land_num < 0 && takeoff_num < 0) close = 1;
			else land_que += land_num, takeoff_que += takeoff_num;
		}
		++total_time;
	}
	if (total_time != 0) --total_time;
	else printf("Current Time: %4d\n", 0); //time
	printf("simulation finished\n");
	printf("simulation time: %4d\n", total_time);
	printf("average waiting time of landing: %4.1f\n", total_land == 0 ? 0 : (double)land_wait / total_land);
	printf("average waiting time of takeoff: %4.1f\n", takeoff_wait == 0 ? 0 : (double)takeoff_wait / total_takeoff);
	int sum = 0;
	for (int i = 0; i < runway_num; ++i)
	{
		printf("runway %02d busy time: %4d\n", i + 1, r[i].total_time);
		sum += r[i].total_time;
	}
	printf("runway average busy time percentage: %4.1f%%\n", total_time == 0 ? 0 : (double)sum / runway_num * 100 / total_time);
	return 0;

}