#pragma once
namespace Bingo {
	typedef std::vector<std::vector<std::string>> BINGO_CARD;
	const cv::Scalar __WHITE__ = cv::Scalar::all(255);
	const cv::Scalar __BLACK__ = cv::Scalar::all(0);
	const std::string DO_NOT_RENDER;

	cv::Mat open_image(const char* _path);
	BINGO_CARD randomize_bingo(BINGO_CARD& card);
	void add_bingo_text(cv::Mat& image, const std::string& text, int x_origin, int y_origin);
	void array_to_card(cv::Mat& card, const BINGO_CARD& cardText, int y_origin);
	std::vector<std::string> split(const std::string& string, char delimiter);
	void _split(const std::string& string, char delimiter, std::vector<std::string>& result);
	std::vector<std::string> pair(const std::vector<std::string>& splitVector);
}