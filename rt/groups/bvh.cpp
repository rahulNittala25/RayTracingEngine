#include <rt/groups/bvh.h>
#include <rt/solids/solid.h>
#include <tuple>

namespace rt {

    BVH::BVH()
    {
        root = new BVHNode();
    }


    void BVH::rebuildIndex() {
        root->primitives = primitives;
        buildRecursive(root);
        std::cout << "Built successfully";
    }

    BBox BVH::getBounds() const {
        return this->root->bbox;
    }

    void BVH::buildRecursive(BVHNode* node)
    {
        Primitive* primitive;
        int primitivesCount = node->primitives.size();
        if (primitivesCount <= 0)
            return;         
        node->bbox = BBox::empty();
        for (int i = 0; i < primitivesCount; i++)
            node->extend(node->primitives[i]->getBounds());

        if (primitivesCount < 3)
        {
            node->isLeaf = true;
            return;                                          
        }


        if (primitivesCount >= 3)                           
        {
            node->isLeaf = false;
            node->left = new BVHNode();
            node->right = new BVHNode();
            Vector diagonal = node->bbox.diagonal();
            int longestSplitAxis = (diagonal.x > diagonal.y && diagonal.x > diagonal.z) ? 0 : (diagonal.y > diagonal.z) ? 1 : 2;

            float axisSplitAlongLen = getCenterPoint(longestSplitAxis, node->bbox);

            if (this->isSAH)
            {
                float lCost = 0, rCost = 0, bestCost = FLT_MAX, cost = 0, kLen;
                for (int k = 1; k < 10; k++)
                {
                    kLen = node->bbox.min.getAxis(longestSplitAxis) + k * (node->bbox.max.getAxis(longestSplitAxis) - node->bbox.min.getAxis(longestSplitAxis)) / 10;
                    int countL = 0, countR = 0;
                    BBox areaL = BBox::empty(), areaR = BBox::empty();
                    for (int i = 0; i < primitivesCount; i++)
                    {
                        float primitiveSplitCenterPoint = getCenterPoint(longestSplitAxis, node->primitives[i]->getBounds());
                        if (primitiveSplitCenterPoint <= kLen) {
                            countL++;
                            areaL.extend(node->primitives[i]->getBounds());
                        }
                        else {
                            countR++;
                            areaR.extend(node->primitives[i]->getBounds());
                        }
                    }
                    if (countL > 0)
                        lCost = countL * areaL.area() / node->bbox.area();
                    if (countR > 0)
                        rCost = countR * areaR.area() / node->bbox.area();
                    cost = lCost + rCost;
                    if (cost <= bestCost) {
                        bestCost = cost;
                        axisSplitAlongLen = kLen;
                    }
                }
            }

            
            for (int i = 0; i < primitivesCount; i++)
            {
                float primitiveSplitMidPoint = getCenterPoint(longestSplitAxis, node->primitives[i]->getBounds());
                if (primitiveSplitMidPoint <= axisSplitAlongLen)
                    node->left->primitives.push_back(node->primitives[i]);
                else
                    node->right->primitives.push_back(node->primitives[i]);
            }
            node->primitives.clear();
            if (node->left->primitives.size() == 0)
            {

                node->left->primitives.push_back(node->right->primitives[0]);
                node->right->primitives.erase(node->right->primitives.begin());
            }

            else if (node->right->primitives.size() == 0)
            {
                node->right->primitives.push_back(node->left->primitives[0]);
                node->left->primitives.erase(node->left->primitives.begin());
            }
            buildRecursive(node->left);
            buildRecursive(node->right);
            return;
        }
    }
    Intersection BVH::intersect(const Ray& ray, float previousBestDistance) const {
        BVHNode* node;
        Intersection nearestIntersection = Intersection::failure();
        std::pair<float, float> d = root->bbox.intersect(ray);
        float t1 = d.first;
        float t2 = d.second;
        if (t1 > t2) {
            // nope
            return nearestIntersection;
        }
        Intersection currentIntersection;
        std::vector<BVHNode*> nodes;
        float entryLeft, exitLeft, entryRight, exitRight;
        nodes.push_back(this->root);

        while (!nodes.empty())
        {
            node = nodes.back();
            nodes.pop_back();

            if (node->isLeaf)
            {
                for (auto prim : node->primitives)
                {
                    currentIntersection = prim->intersect(ray, previousBestDistance);
                    if (currentIntersection)
                    {
                        previousBestDistance = currentIntersection.distance;
                        nearestIntersection = currentIntersection;
                    }
                }
            }
            else
            {
                BBox leftBbox = node->left->bbox;

                std::tie(entryLeft, exitLeft) = leftBbox.intersect(ray);
                if (entryLeft <= exitLeft)
                    nodes.push_back(node->left);

                BBox rightBbox = node->right->bbox;
                std::tie(entryRight, exitRight) = rightBbox.intersect(ray);
                if (entryRight <= exitRight)
                    nodes.push_back(node->right);
            }
        }
        return nearestIntersection;
    }

    float BVH::getCenterPoint(int axis, BBox bbox) {
        if (axis == 0)
            return (bbox.min.x + bbox.max.x) / 2;
        else if (axis == 1)
            return (bbox.min.y + bbox.max.y) / 2;
        else
            return (bbox.min.z + bbox.max.z) / 2;
    }

    void BVH::add(Primitive* p) {
        primitives.push_back(p);
    }

    void BVH::setMaterial(Material* m) {
        for (int i = 0; i < this->primitives.size(); i++) {
            this->primitives[i]->setMaterial(m);
        }
    }

    void BVH::setCoordMapper(CoordMapper* cm) {
        for (int i = 0; i < this->primitives.size(); i++) {
            this->primitives[i]->setCoordMapper(cm);
        }
    }

    void BVH::serialize(BVH::Output& output) {
        // To implement this function:
        // - Call output.setNodeCount() with the number of nodes in the BVH
        /* TODO */
        // - Set the root node index using output.setRootId()
        /* TODO */
        // - Write each and every one of the BVH nodes to the output using output.writeNode()
        /* TODO */ NOT_IMPLEMENTED;
    }
    void BVH::deserialize(BVH::Input& input) {
        // To implement this function:
        // - Allocate and initialize input.getNodeCount() nodes
        /* TODO */
        // - Fill your nodes with input.readNode(index)
        /* TODO */
        // - Use the node at index input.getRootId() as the root node
        /* TODO */ NOT_IMPLEMENTED;
    }

}