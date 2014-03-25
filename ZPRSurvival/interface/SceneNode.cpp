#include "SceneNode.h"

SceneNode::SceneNode () {
	parent = nullptr;
}

SceneNode::~SceneNode () {
}

void SceneNode::attachChild (Ptr child)
{
	child->parent = this;		//caller is parent for attached child
	children.push_back (std::move (child));		//insert new child
}

SceneNode::Ptr SceneNode::detachChild (const SceneNode& node)
{
		//lambda-expression search for child; return true if found
	auto found = std::find_if (children.begin (), children.end (), [&] (Ptr& p) -> bool { return p.get () == &node; });
	assert (found != children.end ());
}
