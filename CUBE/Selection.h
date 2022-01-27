#pragma once
#include <vector>
#include <string>

class DataPoint;
class Dimension;
class Cube;
class Fact;
class Measure;

enum class agg_type {
	COUNT,
	SUM,
	AVERAGE
};

// Выборка
class Selection {
public:

	Selection(Cube* a_cube);

	// Создание выборки
	int8_t make(const std::string& a_dim_name, const std::vector<std::string>& a_positions_list, const std::vector<std::string>& a_measure_list = {});

	// Выбор агрегации
	bool aggregation(agg_type a_agg_type,const std::string& a_dimension_name, const std::vector<std::string>& a_measure_list = {});

	// Вывод Выборки
	void print() const;

	// Очистка Выборки
	void clean();

	~Selection();

private:

	// Агрегация - суммирование
	void count(const std::string& a_dimension_name, const std::vector<std::string>& a_measure_list);
	// Агрегация - количество
	void sum(const std::string& a_dimension_name, const std::vector<std::string>& a_measure_list);
	// Агрегация - среднее значение
	void average(const std::string& a_dimension_name, const std::vector<std::string>& a_measure_list);

	// ТочкиДанных Куба, из которых состоит выборка
	std::vector<DataPoint*> m_selection_points;
	// ТочкиДанных/Факты/Метрики, созданные на основе агрегации
	std::vector<DataPoint*> m_aggregation_points;
	std::vector<Fact*> m_aggregation_facts;
	std::vector<Measure*> m_aggregation_measures;
	// Измерение для агрегаций
	Dimension* m_aggregation_dim;
	// Связанный Куб для создания Выборки
	Cube* m_cube;
};