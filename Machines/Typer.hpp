//
//  Typer.hpp
//  Clock Signal
//
//  Created by Thomas Harte on 19/06/2016.
//  Copyright © 2016 Thomas Harte. All rights reserved.
//

#ifndef Typer_hpp
#define Typer_hpp

#include <memory>

namespace Utility {

class Typer {
	public:
		class Delegate {
			public:
				virtual void typer_set_next_character(Typer *typer, char character) = 0;
		};

		Typer(const char *string, int delay, int frequency, Delegate *delegate);
		~Typer();
		void update(int duration);

	private:
		char *_string;
		int _frequency;
		int _counter;
		Delegate *_delegate;
		size_t _string_pointer;
};

class TypeRecipient: public Typer::Delegate {
	public:
		void set_typer_for_string(const char *string)
		{
			_typer = std::unique_ptr<Typer>(new Typer(string, get_typer_delay(), get_typer_frequency(), this));
		}

	protected:
		virtual int get_typer_delay() = 0;
		virtual int get_typer_frequency() = 0;
		std::unique_ptr<Typer> _typer;
};

}

#endif /* Typer_hpp */
