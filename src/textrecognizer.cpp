#include "textrecognizer.h"


const static std::string basePath{ "C:/temp/opencv/textdetector/" };
const static std::string detectorPath = basePath + "frozen_east_text_detection.pb";
const static std::string recModelPath = basePath + "crnn_cs.onnx";

const static std::vector<cv::String> vocabulary = {
"0",
"1",
"2",
"3",
"4",
"5",
"6",
"7",
"8",
"9",
"a",
"b",
"c",
"d",
"e",
"f",
"g",
"h",
"i",
"j",
"k",
"l",
"m",
"n",
"o",
"p",
"q",
"r",
"s",
"t",
"u",
"v",
"w",
"x",
"y",
"z",
"A",
"B",
"C",
"D",
"E",
"F",
"G",
"H",
"I",
"J",
"K",
"L",
"M",
"N",
"O",
"P",
"Q",
"R",
"S",
"T",
"U",
"V",
"W",
"X",
"Y",
"Z",
"!",
"\"",
"#",
"$",
"%",
"&",
"'",
"(",
")",
"*",
"+",
",",
"-",
".",
"/",
":",
";",
"<",
"=",
">",
"?",
"@",
"[",
"\\",
"]",
"^",
"_",
"`",
"{",
"|",
"}",
"~"
};



TextRecognizer::TextRecognizer()
    : recognizer_{ recModelPath }
{
    recognizer_.setDecodeType("CTC-greedy");
    recognizer_.setInputParams(1.0 / 127.5, cv::Size{ 100, 32 }, cv::Scalar{ 127.5,127.5,127.5 });
    recognizer_.setVocabulary(vocabulary);
}



std::string TextRecognizer::rec(cv::Mat& img) {
    return recognizer_.recognize(img);
}

