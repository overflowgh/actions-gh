int explorationLimit() { result = 5 }

module MyPartialFlow = MyFlow::FlowExplorationFwd<explorationLimit/0>;
import MyPartialFlow::PartialPathGraph

from MyPartialFlow::PartialPathNode n, MyPartialFlow::PartialPathNode source, int dist
where MyPartialFlow::partialFlow(source, n, dist)
select source.getNode(), source, n, "PartialFlow from $@ to $@ at distance " + dist, source.getNode(), source.toString(), n.getNode(), n.toString()
