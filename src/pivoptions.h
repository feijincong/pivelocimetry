#ifndef PIV_OPTIONS_H
#define PIV_OPTIONS_H

#include <iostream>
#include <map>
#include <memory>

class PivOptions
{
	public:
		typedef std::unique_ptr<PivOptions> Uptr;
			
		PivOptions();
		PivOptions(std::map<std::string, std::string> optionMap);
		~PivOptions();

		// Getters
		int get_windowWidth();
		int get_windowHeight();
		int get_overlapHoriz();
		int get_overlapVert();
		int get_noPeaks();

		// Setters
		void set_windowWidth(int x);
		void set_windowHeight(int x);
		void set_overlapHoriz(int x);
		void set_overlapVert(int x);
		void set_noPeaks(int n);

		// Print in console
		void print();

	private:
		// Properties
		int _windowWidth,
			_windowHeight,
			_overlapHoriz,
			_overlapVert,
			_noPeaks;
};
#endif
