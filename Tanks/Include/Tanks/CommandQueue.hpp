#ifndef TANKS_COMMANDQUEUE_HPP
#define TANKS_COMMANDQUEUE_HPP

#include <Tanks/Command.hpp>

#include <queue>


class CommandQueue
{
	public:
		void						push(const Command& command);
		Command						pop();
		bool						isEmpty() const;

		
	private:
		std::queue<Command>			mQueue;
};

#endif // TANKS_COMMANDQUEUE_HPP
