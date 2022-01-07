uint32_t list_counter = 0;
	for (std::vector<DataPoint*>::iterator it_dpoint = m_points.begin(); it_dpoint != m_points.end(); it_dpoint++) {
		if ((*it_dpoint)->get_Dimension()->get_name() == a_dim_name) {
			for (std::vector<std::string>::const_iterator it_list = a_positions_list.begin(); it_list != a_positions_list.end(); it_list++) {
				if ((*it_dpoint)->get_Dimension_position() == *it_list) {
					m_selection_points.insert(std::end(m_selection_points), std::begin((*it_dpoint)->get_Fact()->get_DataPoints()), std::end((*it_dpoint)->get_Fact()->get_DataPoints()));
					list_counter++;
					break;
				}
			}
			if (list_counter == a_positions_list.size())
				return;
		}
	}

	uint32_t list_counter = 0;
	for (std::vector<Fact*>::iterator it_fact = m_facts.begin(); it_fact != m_facts.end(); it_fact++) {
		for (std::vector<DataPoint*>::const_iterator it_dpoint = (*it_fact)->get_DataPoints().begin(); it_dpoint != (*it_fact)->get_DataPoints().end(); it_dpoint++) {
			if ((*it_dpoint)->get_Dimension()->get_name() == a_dim_name) {
				for (std::vector<std::string>::const_iterator it_list = a_positions_list.begin(); it_list != a_positions_list.end(); it_list++) {
					if ((*it_dpoint)->get_Dimension_position() == *it_list) {
						m_selection_points.insert(m_selection_points.end(), (*it_fact)->get_DataPoints().begin(), (*it_fact)->get_DataPoints().end());
						list_counter++;
						break;
					}
				}
				break;
			}	
		}
		if (list_counter == a_positions_list.size())
			return;
	}
  
  uint32_t offset, list_counter = 0;
	for (std::vector<Dimension*>::iterator it_dim = m_dims.begin(); it_dim != m_dims.end(); it_dim++) {
		if ((*it_dim)->get_name() == a_dim_name) {
			offset = (it_dim - m_dims.begin());
			break;
		}	
	}
	for (std::vector<DataPoint*>::iterator it_dpoint = m_points.begin() + offset; it_dpoint != m_points.end(); it_dpoint += offset + 1) {
			for (std::vector<std::string>::const_iterator it_list = a_positions_list.begin(); it_list != a_positions_list.end(); it_list++) {
				if ((*it_dpoint)->get_Dimension_position() == *it_list) {
					m_selection_points.insert(std::end(m_selection_points), std::begin((*it_dpoint)->get_Fact()->get_DataPoints()), std::end((*it_dpoint)->get_Fact()->get_DataPoints()));
					list_counter++;
					break;
				}
			}
		if (list_counter == a_positions_list.size())
			return;
		if (it_dpoint - m_points.begin() + offset + 1  >= m_points.size())
			break;
	}
