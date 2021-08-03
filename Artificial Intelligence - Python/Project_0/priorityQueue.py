import heapq

class PriorityQueue:
	def __init__(self):
		self.heap = []
		heapq.heapify(self.heap)
		self.count = 0

	def push(self,item,priority):
		if item not in str(self.heap):
			heapq.heappush(self.heap,(priority,item))
			self.count = self.count + 1
			return True
		return False

	def pop(self):
		if self.isEmpty():
			return None #("No items to pop!!")
		#print('Pop called, Count = ' + str(self.count))
		result = heapq.heappop(self.heap)
		self.count = self.count - 1
		return result[1] #Returns item

	def isEmpty(self):
		if self.count == 0: #Check if PriorityQueue is empty using count
			return True
		else:
			return False

	def update(self,item,priority):
		if item not in str(self.heap): #If item doesnt exist in heap,just push it
			self.push(item,priority)
			return True
		else:
			for heapItem in self.heap:
				if heapItem[1] != item: #heapItem iterator
					continue
				if heapItem[1] == item and priority < heapItem[0]: #If updated priority < current priority
					self.heap.remove(heapItem) #Remove old tuple
					self.count = self.count - 1 #decrement heap size
					self.push(item,priority) #Insert new one
					return True
				elif heapItem[1] == item and priority >= heapItem[0]: #If updated priority > current priority
					return False #Do nothing

def PQSort(numberList):
	if numberList == None:
		return None;

	result = [] #Initialise result
	pqSort = PriorityQueue() 
	for i in numberList:
		pqSort.push(str(i),i) #Push all elements into our Priority Queue
	#print(pqSort.heap)
	for i in numberList:
		if pqSort.isEmpty(): #Case we pushed more than one times the same integer, we only keep it once!
			return result
		result.append(int(pqSort.pop())) #Append push result to result list
	return result


#Driver code working perfectly!

# pq = PriorityQueue()
# pq.push("test1",2)
# pq.push("test2",5)
# pq.push("test3",7)
# pq.push("test4",4)
# pq.update("test_Update",4)
# print(pq.heap)
# pq.update("test_Update",3)
# print(pq.heap)
# pq.update("test_Update",2)
# print(pq.heap)
# pq.update("test_Update",2)
# print(pq.heap)
# print(pq.push("test1",5))
# print(pq.pop())
# print(pq.heap)
# print(pq.pop())
# print(pq.heap)
# print(pq.pop())
# print(pq.heap)
# print(pq.pop())
# print(pq.heap)
# print(pq.pop())
# print(pq.heap)
# print(pq.isEmpty())
# print(pq.pop())
# print(pq.heap)
# numberList = [3,5,2,8,1,6,2]
# print(numberList)
# print(PQSort(numberList))



