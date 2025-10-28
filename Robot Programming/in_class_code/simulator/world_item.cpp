#include "world_item.h"
#include <cstring>

void WorldItemPtrVector::pushBack(WorldItem* new_item) {
  WorldItem** new_items=new WorldItem*[num_items+1];
  if (num_items) {
    memcpy(new_items, _items, sizeof(WorldItem*)*num_items);
  }
  new_items[num_items]=new_item;
  if (num_items)
    delete [] _items;
  _items=new_items;
  ++num_items;
}

WorldItemPtrVector::~WorldItemPtrVector() {
  if(_items)
    delete [] _items;
}


WorldItem::WorldItem(WorldItem* parent, const Isometry2f pose_in_parent):
  _parent(parent),
  _pose_in_parent(pose_in_parent)
{
  if (!_parent)
    return;
  _parent->_children.pushBack(this);
}

void WorldItem::timerTick(float dt){
  for (int i=0; i<_children.num_items; ++i)
    _children.at(i)->timerTick(dt);
}

void WorldItem::draw(cv::Mat canvas, GridMapping& mapping){
  for (int i=0; i<_children.num_items; ++i)
    _children.at(i)->draw(canvas, mapping);
}

WorldItem::~WorldItem() {
  for (int i=0; i<_children.num_items; ++i)
    delete _children.at(i);
}
