#include <iostream>
#include <map>
#include "file_reader.h"
#include "extractor.h"
#include "splitter.h"
#include "file_writer.h"

void getAllFileParts(int argc, const char* argv[], std::list<FilePart *> &parts)
{
	for (int i = 1; i < argc; i++)
	{
		try
		{
			const char * c = argv[i];
			FileReader a(c);
			parts.push_back(a.getFilePart());
		}
		catch (std::string error)
		{
			std::cout << error << std::endl;
		}
	}
}

void pairParts(std::list<FilePart *> &parts, std::map<std::string, Extractor*> &extractors)
{
	std::map<std::string, Extractor*>::iterator iter;
	Extractor * extractor;
	for (FilePart * filePart : parts)
	{
		std::string name = filePart->getName();
		iter = extractors.find(name);
		if (iter == extractors.end())
		{
			extractor = new Extractor();
			extractor->putFilePart(filePart);
			extractors[name] = extractor;
		}
		else
		{
			iter->second->putFilePart(filePart);
		}
	}
	parts.clear();
}

void executeSort(std::map<std::string, Extractor*> &extractors)
{
	for (std::pair<std::string, Extractor*> pair : extractors)
	{
		pair.second->extractAndSortParts();
	}
}

void writeProcessedFiles(std::map<std::string, Extractor*> &extractors)
{
	for (std::pair<std::string, Extractor*> pair : extractors)
	{
		for (FilePart* part : pair.second->getFileParts())
		{
			try
			{
				FileWriter writer(part);
				writer.write();
			}
			catch (std::string error)
			{
				std::cout << error << std::endl;
			}
		}
	}
}

void testSplitter()
{
	std::string data = "\"\'#$%&()*+-/\\:;<=>@[]{}^_`|~aaa aaa. \"\'#$%&()*+-/\\:;<=>@[]{}^_`|~bbb, bbb! \"\'#$%&()*+-/\\:;<=>@[]{}^_`|~ccc ccc?";
	Splitter s(data);
	s.erase();
	if (data != "aaa aaa. bbb, bbb! ccc ccc?")
		std::cout << "Splitter.erase working rly bad with \"\'#$%&()*+-/\\:;<=>@[]{}^_`|~ !" << std::endl;
	/////////////////////////////////
	std::list<std::string> list;
	s.splitBy(".!?", list, false);
	if (list.size() != 3)
		std::cout << "Splitter.splitBy size of list isnt 3!" << std::endl;
	for (std::string str : list)
	{
		if (str != "aaa aaa." && str != " bbb, bbb!" && str != " ccc ccc?")
			std::cout << "Splitter.splitBy working rly bad with !.? !" << std::endl;

		std::list<std::string> sublist;
		Splitter ss(str);
		ss.splitBy(" ", sublist, true);
		if (sublist.size() != 2)
			std::cout << "Splitter.splitBy size of sublist isnt 2!" << std::endl;

		for (std::string str2 : sublist)
		{

			if (str2 != "aaa" && str2 != "aaa." &&
				str2 != "bbb," && str2 != "bbb!" &&
				str2 != "ccc" && str2 != "ccc?")
				std::cout << "Splitter.splitBy working rly bad with spaces!" << std::endl;
		}
	}
	/////////////////////////////////
}

void testSentence()
{
	std::string data = "abd, dec.";
	Sentence s(data);
	s.extractWords();
	s.sort();
	if (s.getWords().size() != 2)
		std::cout << "Sentence wrong size of words!" << std::endl;
	int i = 0;
	
	for (std::list<std::string>::reverse_iterator iter = s.getWords().rbegin(); iter != s.getWords().rend(); iter++)
	{
		if (i == 0 && *iter != "dba,")
			std::cout << "Sentence words are wrongly sorted!" << std::endl;
		if (i == 1 && *iter != "ced")
			std::cout << "Sentence words are wrongly sorted!" << std::endl;
		i++;
	}
}

void testExtractor()
{
	std::string sin = "abd, dec. acc, ewe zae! wewaf ew arrar rga? ewaff...";
	FilePart *sing = new FilePart("single", 0, sin);

	Extractor single;
	single.putFilePart(sing);

	single.extractAndSortParts();

	std::list<FilePart*> &list = single.getFileParts();
	if (list.size() != 1)
		std::cout << "Extractor Wrong size of list" << __LINE__ << std::endl;

	std::string tocompare = list.front()->extractData();

	if (tocompare != "dba, ced. ewe, eaz cca! we rarra fawew agr? ffawe...")
		std::cout << "Extractor processed wrong data!" << __LINE__ << std::endl;
	///////////////////////////
	std::string triple1 = "abd, dec. seess,";
	std::string triple2 = "abd, dec? abd";
	std::string triple3 = "seess, dec... seess!";
	FilePart *trip1 = new FilePart("triple", 1, triple1);
	FilePart *trip2 = new FilePart("triple", 2, triple2);
	FilePart *trip3 = new FilePart("triple", 3, triple3);
	
	Extractor triple;
	triple.putFilePart(trip1);
	triple.putFilePart(trip2);
	triple.putFilePart(trip3);

	triple.extractAndSortParts();
	std::list<FilePart*> &list2 = triple.getFileParts();
	if (list2.size() != 3)
		std::cout << "Extractor Wrong size of list" << __LINE__ << std::endl;

	int i = 0;

	for (FilePart* part : list2)
	{
		if (i == 0)
		{
			tocompare = part->extractData();
			if (tocompare != "dba, ced. ssees,")
				std::cout << "Extractor processed wrong data!" << __LINE__ << std::endl;
		}
		if (i == 1)
		{
			tocompare = part->extractData();
			if (tocompare != "dba, ced? ssees")
				std::cout << "Extractor processed wrong data!" << __LINE__ << std::endl;
		}
		if (i == 2)
		{
			tocompare = part->extractData();
			if (tocompare != "dba, ced... ssees!")
				std::cout << "Extractor processed wrong data!" << __LINE__ << std::endl;
		}
		i++;
	}
}

void test()
{
	testSplitter();
	testSentence();
	testExtractor();
}

int main(int argc, const char* argv[])
{
	if (argc == 1)
	{
		std::cout << "ERROR: No input! Please provide some input! Please push any button to close" << std::endl; 
		getchar();
		return 0;
	}
	if (argc == 2 && std::string(argv[1]) == std::string("test"))
	{
		test();
		std::cout << "If there is no error then everything is fine! Please push any button to close...";
		getchar();
		return 0;
	}

	std::list<FilePart *> parts;
	std::map<std::string, Extractor*> extractors;

	getAllFileParts(argc, argv, parts);

	pairParts(parts, extractors);
	
	executeSort(extractors);

	writeProcessedFiles(extractors);

	std::cout << "Program executed properly. Please push any button to close...";
	getchar();

	for (FilePart * part : parts)
		delete part;
	for (std::pair<std::string, Extractor*> pair : extractors)
		delete pair.second;

	return 0;
}