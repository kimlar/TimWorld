#include "StateManager.h"

StateManager::StateManager(SharedContext* sharedContext)
{
	this->sharedContext = sharedContext;
}

StateManager::~StateManager()
{
}

void StateManager::PushState(State * state)
{
	//Log("StateManager: PushState");

	if (state != nullptr)
	{
		StateAction stateAction;
		stateAction.push = true;
		stateAction.state = state;
		stateQueue.push(stateAction);
	}
}

void StateManager::PopState()
{
	//Log("StateManager: PopState");

	StateAction stateAction;
	stateAction.push = false;

	if (stateQueue.size() > 0)
	{
		//Log("StateManager: PopState ... stateQueue.size() > 0");

		stateAction.state = stateQueue.front().state;
		stateQueue.push(stateAction);
		return;
	}

	if (states.size() > 0)
	{
		//Log("StateManager: PopState ... states.size() > 0");

		stateAction.state = states.top();
		stateQueue.push(stateAction);
		return;
	}

}

State* StateManager::GetCurrentState()
{
	//Log("StateManager: GetCurrentState");

	/*
	if (states.empty())
	{
		Log("StateManager: GetCurrentState ... states.empty()");
		return {};
	}
	*/
	return states.top();
}

void StateManager::Free()
{
	//Log("StateManager: Free()");

	for (int i = 0; i < states.size() +1; i++)
	{
		states.top()->Exit();
		//Log("StateManager: Free() ... CommitTextureChanges()");
		GetSharedContext()->GetResourceManager()->CommitTextureChanges();
		delete states.top();
		states.pop();
	}

	states.empty();
}

void StateManager::ApplyQueue()
{
	//Log("StateManager: ApplyQueue()");

	int qSize = (int)stateQueue.size();
	for (int i = 0; i < qSize; i++)
	{
		if (stateQueue.front().push == true)
		{
			//Log("StateManager: ApplyQueue() ... Push");

			if (!states.empty())
				states.top()->Exit();
			states.push(stateQueue.front().state);
			stateQueue.pop();
			states.top()->Enter();
			GetSharedContext()->GetResourceManager()->CommitTextureChanges();
		}
		else
		{
			//Log("StateManager: ApplyQueue() ... Pop");

			if (!states.empty())
			{
				states.top()->Exit();
				delete states.top();
				states.pop();
				stateQueue.pop();
				if (!states.empty())
				{
					states.top()->Enter();
					GetSharedContext()->GetResourceManager()->CommitTextureChanges();
				}
			}
		}
	}
}

SharedContext* StateManager::GetSharedContext()
{
	return sharedContext;
}
