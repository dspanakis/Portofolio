# multiAgents.py
# --------------
# Licensing Information:  You are free to use or extend these projects for
# educational purposes provided that (1) you do not distribute or publish
# solutions, (2) you retain this notice, and (3) you provide clear
# attribution to UC Berkeley, including a link to http://ai.berkeley.edu.
# 
# Attribution Information: The Pacman AI projects were developed at UC Berkeley.
# The core projects and autograders were primarily created by John DeNero
# (denero@cs.berkeley.edu) and Dan Klein (klein@cs.berkeley.edu).
# Student side autograding was added by Brad Miller, Nick Hay, and
# Pieter Abbeel (pabbeel@cs.berkeley.edu).


from util import manhattanDistance
from game import Directions
import random, util

from game import Agent

class ReflexAgent(Agent):
    """
    A reflex agent chooses an action at each choice point by examining
    its alternatives via a state evaluation function.

    The code below is provided as a guide.  You are welcome to change
    it in any way you see fit, so long as you don't touch our method
    headers.
    """


    def getAction(self, gameState):
        """
        You do not need to change this method, but you're welcome to.

        getAction chooses among the best options according to the evaluation function.

        Just like in the previous project, getAction takes a GameState and returns
        some Directions.X for some X in the set {NORTH, SOUTH, WEST, EAST, STOP}
        """
        # Collect legal moves and successor states
        legalMoves = gameState.getLegalActions()

        # Choose one of the best actions
        scores = [self.evaluationFunction(gameState, action) for action in legalMoves]
        bestScore = max(scores)
        bestIndices = [index for index in range(len(scores)) if scores[index] == bestScore]
        chosenIndex = random.choice(bestIndices) # Pick randomly among the best

        "Add more of your code here if you want to"

        return legalMoves[chosenIndex]

    def evaluationFunction(self, currentGameState, action):
        """
        Design a better evaluation function here.

        The evaluation function takes in the current and proposed successor
        GameStates (pacman.py) and returns a number, where higher numbers are better.

        The code below extracts some useful information from the state, like the
        remaining food (newFood) and Pacman position after moving (newPos).
        newScaredTimes holds the number of moves that each ghost will remain
        scared because of Pacman having eaten a power pellet.

        Print out these variables to see what you're getting, then combine them
        to create a masterful evaluation function.
        """
        # Useful information you can extract from a GameState (pacman.py)
        successorGameState = currentGameState.generatePacmanSuccessor(action)
        newPos = successorGameState.getPacmanPosition()
        newFood = successorGameState.getFood()
        newGhostStates = successorGameState.getGhostStates()
        newScaredTimes = [ghostState.scaredTimer for ghostState in newGhostStates]

        "*** YOUR CODE HERE ***"
        #Get current score
        score = successorGameState.getScore()
		#Get ghost positions and food list        
       	ghostPos = successorGameState.getGhostPositions()
        foodList = newFood.asList()
        #Check if foodlist is empty
        if len(foodList) == 0:
        	return score
        #Get closest food distance
        closestFood = min(manhattanDistance(newPos, foodDot) for foodDot in foodList)
        #Get closest ghost distance
        closestGhost = min(manhattanDistance(newPos, ghost) for ghost in ghostPos)
        #If ghost has gotten too close, punish with a big negative score
        if closestGhost < 2:
        	return -10000
        #Reward based on, the closer to the food the better score we are going to get
        score += closestGhost / (closestFood*10)

        return score



def scoreEvaluationFunction(currentGameState):
    """
    This default evaluation function just returns the score of the state.
    The score is the same one displayed in the Pacman GUI.

    This evaluation function is meant for use with adversarial search agents
    (not reflex agents).
    """
    return currentGameState.getScore()

class MultiAgentSearchAgent(Agent):
    """
    This class provides some common elements to all of your
    multi-agent searchers.  Any methods defined here will be available
    to the MinimaxPacmanAgent, AlphaBetaPacmanAgent & ExpectimaxPacmanAgent.

    You *do not* need to make any changes here, but you can if you want to
    add functionality to all your adversarial search agents.  Please do not
    remove anything, however.

    Note: this is an abstract class: one that should not be instantiated.  It's
    only partially specified, and designed to be extended.  Agent (game.py)
    is another abstract class.
    """

    def __init__(self, evalFn = 'scoreEvaluationFunction', depth = '2'):
        self.index = 0 # Pacman is always agent index 0
        self.evaluationFunction = util.lookup(evalFn, globals())
        self.depth = int(depth)

class MinimaxAgent(MultiAgentSearchAgent):
    """
    Your minimax agent (question 2)
    """

    def getAction(self, gameState):
        """
        Returns the minimax action from the current gameState using self.depth
        and self.evaluationFunction.

        Here are some method calls that might be useful when implementing minimax.

        gameState.getLegalActions(agentIndex):
        Returns a list of legal actions for an agent
        agentIndex=0 means Pacman, ghosts are >= 1

        gameState.generateSuccessor(agentIndex, action):
        Returns the successor game state after an agent takes an action

        gameState.getNumAgents():
        Returns the total number of agents in the game

        gameState.isWin():
        Returns whether or not the game state is a winning state

        gameState.isLose():
        Returns whether or not the game state is a losing state
        """
        "*** YOUR CODE HERE ***"

        action, score = self.getValue(0,0, gameState)
        return action
        # util.raiseNotDefined()

    def getValue(self, curDepth, agentIndex, curGameState):
    	if len(curGameState.getLegalActions(agentIndex)) == 0:
    		return None,self.evaluationFunction(curGameState)
    	
    	if curDepth == self.depth:
    		return None,self.evaluationFunction(curGameState)
    	
    	if curGameState.isLose() or curGameState.isWin():
    		return None, self.evaluationFunction(curGameState)

    	if agentIndex == 0:
    		return self.maxVal(curDepth, agentIndex, curGameState)

    	if agentIndex != 0:
    		return self.minVal(curDepth,agentIndex, curGameState)

    def maxVal(self, curDepth, agentIndex, curGameState):

    	movesArray = curGameState.getLegalActions(agentIndex)
    	maxValue = float('-Inf')
    	maxAction = None

    	for action in movesArray:
    		nextGameState = curGameState.generateSuccessor(agentIndex, action)
    		nextAgentIndex = agentIndex + 1
    		nextDepth = curDepth

    		temp, minValue = self.getValue(nextDepth, nextAgentIndex, nextGameState)

    		if minValue > maxValue:
    			maxValue = minValue
    			maxAction = action

    	return maxAction, maxValue

    def minVal(self, curDepth, agentIndex, curGameState):
    	movesArray = curGameState.getLegalActions(agentIndex)
    	minValue = float('Inf')
    	minAction = None

    	for action in movesArray:
    		nextGameState = curGameState.generateSuccessor(agentIndex, action)
    		nextAgentIndex = agentIndex + 1
    		nextDepth = curDepth

    		#Case we reached end of ghosts
    		if nextAgentIndex == curGameState.getNumAgents():
    			nextAgentIndex = 0
    			nextDepth = curDepth + 1

    		temp, maxValue = self.getValue(nextDepth, nextAgentIndex, nextGameState)

    		if maxValue < minValue:
    			minValue = maxValue
    			minAction = action

    	return minAction, minValue


class AlphaBetaAgent(MultiAgentSearchAgent):
    """
    Your minimax agent with alpha-beta pruning (question 3)
    """

    def getAction(self, gameState):
        """
        Returns the minimax action using self.depth and self.evaluationFunction
        """
        "*** YOUR CODE HERE ***"
        action, score = self.getValue( 0, 0, float('-Inf'), float('Inf'), gameState)

        return action
        # util.raiseNotDefined()

    def getValue(self, curDepth, agentIndex, alpha, beta, curGameState):
    	if len(curGameState.getLegalActions(agentIndex)) == 0:
    		return None,self.evaluationFunction(curGameState)
    	
    	if curDepth == self.depth:
    		return None,self.evaluationFunction(curGameState)
    	
    	if curGameState.isLose() or curGameState.isWin():
    		return None, self.evaluationFunction(curGameState)

    	if agentIndex == 0: #If its pacman
    		return self.maxValue(curDepth, agentIndex, alpha, beta, curGameState)

    	if agentIndex != 0: #If its ghost
    		return self.minValue(curDepth,agentIndex, alpha, beta, curGameState)

    def maxValue(self, curDepth, agentIndex, alpha, beta, curGameState):
    	movesArray = curGameState.getLegalActions(agentIndex)
    	maxValue = float('-Inf')
    	maxAction = None

    	for action in movesArray:
    		nextGameState = curGameState.generateSuccessor(agentIndex, action)
    		nextAgentIndex = agentIndex + 1
    		nextDepth = curDepth

    		temp, minValue = self.getValue(nextDepth, nextAgentIndex, alpha, beta, nextGameState)

    		if minValue > maxValue:
    			maxValue = minValue
    			maxAction = action

    		alpha = max(alpha, maxValue)

    		if maxValue > beta: #Pruning condition
    			return maxAction, maxValue

    	return maxAction, maxValue


    def minValue(self, curDepth, agentIndex, alpha, beta, curGameState):
        movesArray = curGameState.getLegalActions(agentIndex)
        minValue = float('+Inf')
        minAction = None

        for action in movesArray:
            nextGameState = curGameState.generateSuccessor(agentIndex, action)
            nextAgentIndex = agentIndex + 1
            nextDepth = curDepth

            #Case we reached end of ghosts
            if nextAgentIndex == curGameState.getNumAgents():
                nextAgentIndex = 0
                nextDepth = curDepth + 1

            temp, maxValue = self.getValue(nextDepth, nextAgentIndex, alpha, beta, nextGameState)

            if maxValue < minValue:
                minValue = maxValue
                minAction = action

            beta = min(beta, minValue)
            if minValue < alpha:
                return minAction, minValue

        return minAction, minValue

class ExpectimaxAgent(MultiAgentSearchAgent):
    """
      Your expectimax agent (question 4)
    """

    def getAction(self, gameState):
        """
        Returns the expectimax action using self.depth and self.evaluationFunction

        All ghosts should be modeled as choosing uniformly at random from their
        legal moves.
        """
        "*** YOUR CODE HERE ***"
        action, score = self.getValue(0, 0, gameState)

        return action
        # util.raiseNotDefined()

    def getValue(self, curDepth, agentIndex, curGameState):
        if len(curGameState.getLegalActions(agentIndex)) == 0:
    	    return None,self.evaluationFunction(curGameState)
        
        if curDepth == self.depth:
            return None,self.evaluationFunction(curGameState)
  
        if curGameState.isLose() or curGameState.isWin():
            return None, self.evaluationFunction(curGameState)

        if agentIndex == 0:
            return self.maxValue(curDepth, agentIndex, curGameState)

        if agentIndex != 0:
    	    return self.expectedValue(curDepth,agentIndex, curGameState)

    def maxValue(self, curDepth, agentIndex, curGameState):
    	movesArray = curGameState.getLegalActions(agentIndex)
    	maxValue = float('-Inf')
    	maxAction = None

    	for action in movesArray:
    		nextGameState = curGameState.generateSuccessor(agentIndex, action)
    		nextAgentIndex = agentIndex + 1
    		nextDepth = curDepth

    		temp, minValue = self.getValue(nextDepth, nextAgentIndex, nextGameState)

    		if minValue > maxValue:
    			maxValue = minValue
    			maxAction = action

    	return maxAction, maxValue
    
    def expectedValue(self, curDepth, agentIndex, curGameState):
        movesArray = curGameState.getLegalActions(agentIndex)
        expectedValue = 0
        expectedAction = None

        #propability based on len of moves array
        propability = 1.0 / len(movesArray)

        for action in movesArray:
            nextGameState = curGameState.generateSuccessor(agentIndex, action)
            nextAgentIndex = agentIndex + 1
            nextDepth = curDepth

            #Case we reached end of ghosts
            if nextAgentIndex == curGameState.getNumAgents():
                nextAgentIndex = 0
                nextDepth = curDepth + 1

            temp , nextValue = self.getValue(nextDepth, nextAgentIndex, nextGameState)

            #Sum all expected values (propability*value1 + propability*value2 + ...) as we were taught in class
            expectedValue += propability * nextValue

        return expectedAction, expectedValue #We dont care about expected action, it could be none

def betterEvaluationFunction(currentGameState):
    """
    Your extreme ghost-hunting, pellet-nabbing, food-gobbling, unstoppable
    evaluation function (question 5).

    DESCRIPTION: <write something here so we know what you did>

	First we create an array with the weights of how important is for the pacman to take into account
	->Food
	->Current Score
	->Remaining Food
	->Power Capsules count

	if a ghost get too close, we make pacman think food is way to far from us, so that it will only escape
	
	return a weighted result based on our state evaluation
    """
    "*** YOUR CODE HERE ***"
    weights = [("ClosestFood", 5), ("Game Score", 200), ("Remaining Food", -150),("Remaining Capsules", -5)]

    pacmanPos = currentGameState.getPacmanPosition()
    ghostList = currentGameState.getGhostPositions()

    closestGhost = min(manhattanDistance(pacmanPos, ghostPos) for ghostPos in ghostList)

    gameScore = currentGameState.getScore()

    foodList = currentGameState.getFood().asList()
    closestFoodDot = 1
    remainingFood = len(foodList)
    
    if remainingFood != 0:
        closestFoodDot = min(manhattanDistance(pacmanPos, foodDot) for foodDot in foodList)

    if closestGhost < 2:
        closestFoodDot = 9999

    remainingCapsules = len(currentGameState.getCapsules())
    
    resultScore = weights[0][1]*(1.0/closestFoodDot) + weights[1][1]*gameScore + weights[2][1]*remainingFood + weights[3][1]*remainingCapsules

    return resultScore
# Abbreviation
better = betterEvaluationFunction
