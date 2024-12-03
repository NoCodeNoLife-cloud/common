// Created by author ethereal on 2024/11/27.
// Copyright (c) 2024 ethereal. All rights reserved.
#ifndef CLASS_HPP
#define CLASS_HPP
#include <boost/type_index.hpp>

namespace common::entity::util
{
	/// \brief Utility class for the operations related to C++ class or type.
	class Class abstract
	{
	public:
		template <typename T>
		static std::string getTypeId(T t)
		{
			return boost::typeindex::type_id_with_cvr<decltype(t)>().pretty_name();
		}
	};
}
#endif //CLASS_HPP
