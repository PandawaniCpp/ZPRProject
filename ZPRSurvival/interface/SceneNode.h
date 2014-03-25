#pragma once
#include <memory>
#include <vector>
#include <cassert>
#include <algorithm>

class SceneNode {
public:
	typedef std::unique_ptr<SceneNode> Ptr;		//very often use of this particular unique_ptr

	SceneNode ();
	virtual ~SceneNode ();

	void SceneNode::attachChild (Ptr child);	//add child to vector 'children'
	SceneNode::Ptr SceneNode::detachChild (const SceneNode& node);	//remove child from vector

private:
	std::vector<Ptr> children;
	SceneNode* parent;
};

