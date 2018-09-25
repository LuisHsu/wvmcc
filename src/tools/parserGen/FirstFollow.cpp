//    Copyright 2018 Luis Hsu
// 
//    Licensed under the Apache License, Version 2.0 (the "License");
//    you may not use this file except in compliance with the License.
//    You may obtain a copy of the License at
// 
//        http://www.apache.org/licenses/LICENSE-2.0
// 
//    Unless required by applicable law or agreed to in writing, software
//    distributed under the License is distributed on an "AS IS" BASIS,
//    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//    See the License for the specific language governing permissions and
//    limitations under the License.

#include <parserGen/FirstFollow.hpp>

static void free_FirstFollow_data(void* data){
    FirstFollowMap* firstfollowMap = (FirstFollowMap*)data;
    delete firstfollowMap;
}
static void free_FirstFollow(Buffer** bufferPtr){
    FirstFollow* firstfollow = (FirstFollow*)*bufferPtr;
    delete firstfollow;
    *bufferPtr = nullptr;
}
FirstFollow::FirstFollow(){
    buffer.data = new FirstFollowMap;
    buffer.length = 0;
    buffer.free = free_FirstFollow;
}
FirstFollow::~FirstFollow(){
    free_FirstFollow_data(buffer.data);
}
Buffer* FirstFollow::getBuffer(){
    return &buffer;
}
FirstFollowMap::iterator FirstFollow::begin(){
    FirstFollowMap* firstfollowMap = (FirstFollowMap*)buffer.data;
    return firstfollowMap->begin();
}
FirstFollowMap::iterator FirstFollow::end(){
    FirstFollowMap* firstfollowMap = (FirstFollowMap*)buffer.data;
    return firstfollowMap->end();
}
FirstFollowMap::iterator FirstFollow::find(const std::string target){
    FirstFollowMap* firstfollowMap = (FirstFollowMap*)buffer.data;
    return firstfollowMap->find(target);
}
void FirstFollow::addElement(const std::string target, const std::string element){
    FirstFollowMap* firstfollowMap = (FirstFollowMap*)buffer.data;
    (*firstfollowMap)[target].push_back(element);
    (*firstfollowMap)[target].unique();
}