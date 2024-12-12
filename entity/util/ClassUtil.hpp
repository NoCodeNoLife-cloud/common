// Created by author ethereal on 2024/11/27.
// Copyright (c) 2024 ethereal. All rights reserved.
#pragma once
#include <boost/type_index.hpp>

namespace common::entity::util
{
/// \brief Utility class for the operations related to C++ class or type.
class ClassUtil abstract
{
public:
	template <typename T> static std::string getTypeId([[maybe_unused]] T t);
};

template <typename T> std::string ClassUtil::getTypeId(T t) {
	return boost::typeindex::type_id_with_cvr<decltype(t)>().pretty_name();
}
}
