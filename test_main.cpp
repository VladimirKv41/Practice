double facts[5][20] =
{
	{21,17,14,16,25,20,16,13,12,23,15,17,14,16,21,20,17,13,12,21},
	{19,18,18,20,19,18,17,17,15,23,19,27,21,20,24,24,17,18,19,21},
	{20,18,17,17,20,20,18,17,17,20,17,15,21,17,24,21,18,16,17,19},
	{12,12,14,15,14,13,13,15,14,15,16,17,16,15,13,14,17,20,16,13},
	{25,26,25,24,26,26,27,30,25,26,27,28,28,30,29,29,28,31,29,28}
};

std::string cities[5] = { "Зеленоград" , "Ржев", "Тверь" , "Cанкт-Петербург", "Cевастополь"};
std::string dates[20] = { 
	"15 мая" , "16 мая", "17 мая" , "18 мая", "19 мая",
	"20 мая" , "21 мая", "22 мая" , "23 мая", "25 мая",
	"26 мая" , "27 мая", "28 мая" , "29 мая", "30 мая",
	"31 мая" , "1 июня", "2 июня" , "3 июня", "4 июня"
};

int main() {
	srand(time(NULL));
	setlocale(LC_ALL, "Russian");
	std::string dimension[2] = { "Город","Дата" };
	std::string measures[1] = {"Температура"};
	double  elapsed_ns = 0;
	long k = 0;
	Cube* cube = new Cube();
	cube->add_Dimension(dimension[0]);
	cube->add_Dimension(dimension[1]);
	cube->add_Measure(measures[0]);
	for (int city_c = 0; city_c < 2000; city_c++) {
		for (int date_c = 0; date_c < 2000; date_c++) {
			cube->add_Fact((double)(rand() % 60 - 30), "Температура", { cities[city_c % 5] + std::to_string(city_c),std::to_string(date_c + 1) + " месяца" });
		}
	}
	while (k < 100000) {
		auto begin = std::chrono::steady_clock::now();
		cube->selection("Дата", {"15 месяца", "116 месяца" , "117 месяца" , "1999 месяца"});
		auto end = std::chrono::steady_clock::now();
		elapsed_ns += std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
		k++;
		cube->clean_selection();
	}
	std::cout << std::setprecision(4) << (elapsed_ns / 100000) / 1000000;
	delete cube;
	_CrtDumpMemoryLeaks();
	return 0;
}
