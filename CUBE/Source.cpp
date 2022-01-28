#include <iostream>
#include <vector>
#include <map>
#include <locale>
#include <chrono>
#include <iomanip>
#include "Cube.h"
#include "Selection.h"
#define __CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW


//double facts_temp[5][20] =
//{
//	{21,17,14,16,25,20,16,13,12,23,15,17,14,16,21,20,17,13,12,21},
//	{19,18,18,20,19,18,17,17,15,23,19,27,21,20,24,24,17,18,19,21},
//	{20,18,17,17,20,20,18,17,17,20,17,15,21,17,24,21,18,16,17,19},
//	{12,12,14,15,14,13,13,15,14,15,16,17,16,15,13,14,17,20,16,13},
//	{25,26,25,24,26,26,27,30,25,26,27,28,28,30,29,29,28,31,29,28}
//};
//
//double facts_hum[5][20] =
//{
//	{81,67,64,66,75,70,66,63,72,73,65,67,64,66,71,70,77,63,62,71},
//	{69,78,68,70,69,68,67,77,65,83,69,77,71,70,74,84,67,78,69,71},
//	{70,68,77,67,70,70,78,67,67,70,77,65,71,67,84,71,68,66,77,69},
//	{62,62,64,75,64,73,63,65,64,65,66,77,66,75,63,64,67,70,66,73},
//	{75,76,75,74,86,76,77,80,75,76,77,78,88,80,79,79,78,81,79,78}
//};
//
//std::string cities[5] = { "Зеленоград" , "Ржев", "Тверь" , "Санкт-Петербург", "Cевастополь"};
//std::string dates[20] = { 
//	"15 мая" , "16 мая", "17 мая" , "18 мая", "19 мая",
//	"20 мая" , "21 мая", "22 мая" , "23 мая", "25 мая",
//	"26 мая" , "27 мая", "28 мая" , "29 мая", "30 мая",
//	"31 мая" , "1 июня", "2 июня" , "3 июня", "4 июня"
//};


//double facts_check[5][20] =
//{
//	{481.41,67,64,66,75,70,66,63,72,73,65,67,64,66,71,70,77,63,62,71},
//	{69,78,68,70,69,68,67,77,65,83,69,77,71,70,74,84,67,78,69,71},
//	{70,68,77,67,70,70,78,67,67,70,77,65,71,67,84,71,68,66,77,69},
//	{62,62,64,75,64,73,63,65,64,65,66,77,66,75,63,64,67,70,66,73},
//	{75,76,75,74,86,76,77,80,75,76,77,78,88,80,79,79,78,81,79,78}
//};

int main() {
	std::vector<std::string> food = { "Пицца" , "Оливье", "Чай" , "Вода", "Кофе" };
	std::vector<std::string> datetime = {
		"15 мая 16:00" , "16 мая 13:46", "16 мая 15:06" , "16 мая 16:45", "17 мая 11:13",
		"20 мая 14:07" , "21 мая 10:22", "21 мая 15:54" , "22 мая 15:00", "22 мая 16:37",
		"26 мая 12:03" , "27 мая 14:32", "28 мая 15:11" , "29 мая 11:56", "30 мая 14:23",
		"31 мая 11:07" , "1 июня 10:15", "2 июня 16:17" , "3 июня 13:23", "4 июня 15:13"
	};
	std::vector<std::string> year = {
		"2019" , "2020", "2021"
	};
	std::vector<std::string> dimensions = { "Покупка","Дата и время","Год" };
	std::vector<std::string> measures = { "Цена", "Масса" };
	srand(time(NULL));
	setlocale(LC_ALL, "Russian");
	Cube* cube = new Cube();
	cube->add_Dimension(dimensions[2]);
	cube->add_Dimension(dimensions[1]);
	cube->add_Dimension(dimensions[0]);
	cube->add_Measure(measures[1]);
	cube->add_Measure(measures[0]);
	for (int year_c = 0; year_c < 3; year_c++) {
		int n_datetime = rand() % 20;
		for (int datetime_c = 0; datetime_c < n_datetime; datetime_c++) {
			int n_food = rand() % 5;
			for (int food_c = 0; food_c < n_food; food_c++) {
				cube->add_Fact(rand() % 1000 + 100, "Цена", { year[year_c],datetime[datetime_c],food[food_c] });
				cube->add_Fact(rand() % 2000 + 100, "Масса", { year[year_c],datetime[datetime_c],food[food_c] });
			}
		}
	}
	Selection* select = new Selection(cube);
	select->make("Покупка", { "Пицца", "Вода" }, { "Цена" });
	select->print();
	select->make("Дата и время", { "15 мая 16:00" , "16 мая 13:46", "16 мая 15:06" , "16 мая 16:45", "17 мая 11:13", "31 мая 11:07" , "1 июня 10:15" });
	select->print();
	select->aggregation(agg_type::AVERAGE, "Дата и время");
	select->print();
	
	delete cube;
	delete select;
	dimensions.~vector();
	measures.~vector();
	food.~vector();
	datetime.~vector();
	year.~vector();

	_CrtDumpMemoryLeaks();
	return 0;
}