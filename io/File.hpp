// Created by author ethereal on 2024/12/3.
// Copyright (c) 2024 ethereal. All rights reserved.
#pragma once
#include <chrono>
#include <filesystem>
#include <string>
#include <vector>
#include "entity/interface/IfaceComparable.hpp"

namespace common::io
{
/// \brief Represents a file or directory in the file system.
/// \details This class provides the methods to operate on a file or directory.
/// It is used to represent a file or directory in the file system.
class File final : public interface::IfaceComparable<File>
{
public:
	explicit File(const std::string& path);
	explicit File(std::filesystem::path path);
	explicit File(const char* path);
	~File() override;
	[[nodiscard]] auto compareTo(const File& other) const -> int override;
	[[nodiscard]] auto equals(const File& other) const -> bool override;
	[[nodiscard]] auto canExecute() const -> bool;
	[[nodiscard]] auto canRead() const -> bool;
	[[nodiscard]] auto canWrite() const -> bool;
	[[nodiscard]] auto createNewFile() const -> bool;
	static auto createTempFile(const std::string& prefix, const std::string& suffix, const std::string& directory = "") -> File;
	[[nodiscard]] auto deleteFile() const -> bool;
	[[nodiscard]] auto exists() const -> bool;
	[[nodiscard]] auto getAbsolutePath() const -> std::string;
	[[nodiscard]] auto getAbsoluteFile() const -> File;
	[[nodiscard]] auto getName() const -> std::string;
	[[nodiscard]] auto getParent() const -> std::string;
	[[nodiscard]] auto getCanonicalFile() const -> File;
	[[nodiscard]] auto getParentFile() const -> File;
	[[nodiscard]] auto getPath() const -> std::string;
	[[nodiscard]] auto getTotalSpace() const -> long;
	[[nodiscard]] auto getUsableSpace() const -> long;
	[[nodiscard]] auto hashCode() const -> size_t;
	[[nodiscard]] auto isAbsolute() const -> bool;
	[[nodiscard]] auto mkdir() const -> bool;
	[[nodiscard]] auto renameTo(const File& dest) const -> bool;
	[[nodiscard]] auto isDirectory() const -> bool;
	[[nodiscard]] auto isFile() const -> bool;
	[[nodiscard]] auto isHidden() const -> bool;
	[[nodiscard]] auto length() const -> long long;
	[[nodiscard]] auto lastModified() const -> long long;
	[[nodiscard]] auto list() const -> std::vector<std::string>;
	[[nodiscard]] auto toString() const -> std::string;
	[[nodiscard]] auto toURI() const -> std::string;

private:
	std::filesystem::path filePath_;
	friend std::formatter<File>;
};
}

template <> struct std::formatter<common::io::File>
{
	constexpr static auto parse(format_parse_context& ctx) -> format_parse_context::const_iterator;
	static auto format(const common::io::File& content, format_context& ctx) -> back_insert_iterator<_Fmt_buffer<char>>;
};

/**
 * \brief Parse the format specifiers for the File class.
 *
 * This function parses the format specifiers for the File class.
 * The format specifiers are as follows:
 *
 * \param ctx The format parse context.
 * \return The parsed format specifiers.
 */
constexpr auto std::formatter<common::io::File>::parse(format_parse_context& ctx) -> format_parse_context::const_iterator {
	const auto begin = ctx.begin();
	if (const auto end = ctx.end(); begin != end && *begin != '}') {
		throw std::format_error("invalid format");
	}
	return begin;
}

/**
 * \brief Format the File object into a string.
 *
 * This function formats the File object using the provided format context.
 * It generates a string representation of the File object.
 *
 * \param content The File object to format.
 * \param ctx The format context to use for formatting.
 * \return An iterator to the end of the inserted sequence.
 */
inline auto std::formatter<common::io::File>::format(const common::io::File& content, format_context& ctx) -> back_insert_iterator<_Fmt_buffer<char>> {
	return std::format_to(ctx.out(), "File{{path: {}}}", content.filePath_.string());
}

inline auto operator<<(std::ostream& os, const common::io::File& content) -> std::ostream& {
	return os << std::format("{}", content);
}
