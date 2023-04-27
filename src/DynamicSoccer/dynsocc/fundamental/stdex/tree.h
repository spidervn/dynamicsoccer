#ifndef DYNSOCC_FUNDAMENTAL_STDEX_TREE_H_
#define DYNSOCC_FUNDAMENTAL_STDEX_TREE_H_

#include <vector>
#include <string>
#include <queue>



namespace dynsocc
{
    struct TreeEx
    {   
        std::string strData;
        int iData;
        double dData;

        std::vector<TreeEx>* v;
        TreeEx();

        int addNode(TreeEx e);
        void operator=(const TreeEx& t);

		  bool hasChild();
		  const std::vector<TreeEx>* getVChild();
    };

    struct TreeVec;
	 typedef unsigned char TreeNodeAddr;
	 struct TreeVecNode
	 {
		 int myid;
		 int parentid;
		 std::vector<int> childid;

		 int data;
	 };

    // Tree based on vector
    struct ITreeVecTravesal
    {
        // Node => If you remove node from tree here => crash 
        virtual int onTravelNode(TreeVecNode& node) = 0;
    };

    // Definition of a Tree.
    struct TreeNodeAddress
	{
		 unsigned char a[10];	// Maximum 10 Tree Level
         int n;
         int myRaw;

         TreeNodeAddress()
         {
             n = 0;
         }
	};

    /* 
     * Implement a tree with:
     *  (1) Maximum 10 deep level
     */
    struct TreeVec
    {
        std::vector<TreeVecNode> data;      // Raw data
        TreeNodeAddress mapTrR[100];        // Map TreeAddress to RawData address
                                            // mapTrR: TreeAddress -> RawAddress)
        TreeNodeAddress addr001;
        unsigned char* buffer;

        TreeVecNode newNode()
        {
            TreeVecNode n1;
            n1.myid = data.size();
            n1.parentid = -1;
            n1.childid.clear();

            data.push_back(n1);
       }

        TreeVecNode newChildNode(int parentId)
        {
            TreeVecNode n1;
            n1.myid = data.size();
            n1.parentid = -1;
            n1.childid.clear();

            data.push_back(n1);


            // Relationship Between 
        }

        int removeNode(int nodeId)
        {
            // Remove ID => Recalculate whole ID? 
            // 
            int i = 0;
            data[i];

            return 0;
        }

        int getChild(int nodeId, std::vector<TreeVecNode>& vchild)
        {
            vchild.clear();
            int l01 = data.size();

            for (int i=0; i<l01; ++i)
            {
                
            }
            return 0;
        }

        // Think: remove node while travelling all node? 
        void travesalAllChildNode(TreeVecNode& node, ITreeVecTravesal* p)
        {
            // 
            // int a;
            // 
            int a[100];
            int n;
            n = 0;

            p->onTravelNode(node);

            std::queue<TreeVecNode> qnode;
            TreeVecNode n1 = qnode.front();

            for (unsigned int i=0; i<node.childid.size();++i)
            {
                qnode.push(data[node.childid[i]]);
            }
            
            while (qnode.size() > 0)
            {
                TreeVecNode trvnode;
                trvnode = qnode.front();
                qnode.pop();
                
                p->onTravelNode(trvnode);
                for (unsigned int i=0; i<trvnode.childid.size(); ++i)
                {
                    qnode.push(data[trvnode.childid[i]]);
                }
            }
        }
    };

	#define ADJTREE_MAX_NODE 100
	#define ADJTREE_MAX_EDGE ADJTREE_MAX_NODE-1

    struct TreeAdjMetaNode
    {
        std::string name;
        int id;
        int parent_id;
        // Children??

        TreeAdjMetaNode()
        {
            id=-1;
            parent_id=-1;
        }
    };

    class TreeAdj
    {
		 
		/* 
			Primitive Operations: 
			+ Node LifeCycle 
				- Node Address:
					+ ID (Unique value) 
					+ Location (Physical location: index)
				- Manage Node List Data (vector Node)
				- Mange Node 
			+ Edge LifeCycle 

		 
		 */
        // std::string _vname[ADJTREE_MAX_NODE];
        TreeAdjMetaNode _vnode[ADJTREE_MAX_NODE];
		int _auto_id;
		int _nNode;

        int _v_edge_l[ADJTREE_MAX_EDGE];
        int _v_edge_r[ADJTREE_MAX_EDGE];
		int _n_edge;

		int _nRootID;	// RootNode

		// Binary Tree - Mapping (AutoID - Index)
		int _m_id2index_l[ADJTREE_MAX_NODE];
		int _m_id2index_r[ADJTREE_MAX_NODE];
		int _n_id2index;

		// Binary Tree Mapping (Name - ID)
		std::string _m_name2id_l[ADJTREE_MAX_NODE];
		int _m_name2id_r[ADJTREE_MAX_NODE];
		int _n_name2id;


	public:
		TreeAdj();
        int add_node(int parent_id, std::string name, int &nodeID);		// Parent-ID < 0 => Adding a root node 
		int get_node(int ID, std::string& data);
        int remove_node(int node_id);

        int get_root_node(int &nodeid, std::string& name);

        int get_children(int nodeid, std::vector<int>& vchildren, std::vector<std::string>& vname);

		int count_node();
		int count_edge();

        int get_descentdants(int node_id, std::vector<int>& vid, std::vector<std::string>& vname);
        int get_descentdants(std::vector<int> vnodeid, std::vector<int>& vid, std::vector<std::string>& vname);
        int branch_population(int node_id);
        int branches_population(std::vector<int> node_id);

        //
        // v_edge_l[i]=n
        // v_edge_r[i]=m
        //  => n is parent node of m.
        // 
        // Tree-ID.
        //  vid[1]=i => 
    };


	class test_adjtree
	{
	public:
		static void test();
		
	};

	class algorithm
	{
	public: 
		template <typename T>
		static int binary_search(T* arr_sorted_asc, int nBegin, int nEnd, T val, int& nFound)
		{
			int nL = nBegin;
			int nR = nEnd-1;
			int nMid;
			nFound = -1;
			T valMid;
			while (nL <= nR && (nFound < 0))
			{
				nMid = (nL + nR) / 2;
				valMid = arr_sorted_asc[nMid];

				if (valMid == val)
				{
					nFound = nMid;
				}
				else if (valMid < val)
				{
                    nL = nMid + 1;
				}
                else 
                {
                    nR = nMid - 1;
                }
			}

			return 0;
		}

        template <typename T>
        static int binary_search(T* arr_sorted_asc, int nBegin, int nEnd, T val, int& nFoundBegin, int& nFoundEnd)
        {
            // Find every 
            int nL = nBegin;
            int nR = nEnd-1;
            int nMid = (nL + nR) / 2;
            int nFound = -1;
            nFoundBegin = -1;
            nFoundEnd = -1;
			T valMid;

            // The 1st location 
            while (nL <= nR && (nFound < 0))
            {
				nMid = (nL + nR) / 2;
                valMid = arr_sorted_asc[nMid];

                if (valMid == val)
                {
                    nFound = nMid;
                }
                else if (valMid < val)
                {
                    nL = nMid + 1;
                }
                else 
                {
                    nR = nMid - 1;
                }
            }

            if (nFound >=0)
            {
                nFoundBegin = nFound;
                nFoundEnd = nFound;


                while (nFoundBegin > nBegin && arr_sorted_asc[nFoundBegin-1] == val)  { nFoundBegin--;}
                while (nFoundEnd < nEnd-1 && arr_sorted_asc[nFoundEnd+1] == val ) { nFoundEnd++;}
            }
            
            return 0;
        }

        
		template<typename T>
		static int insert_into_sorted_asc(T* parr, int nBegin, int nEnd, T val, int& nPos)
		{
            // Pre-Requisite: parr is sorted asc (every i: p[i] <= p[i+1])
            // This function does not validate pre-requisite condition 
           
            // Find the 1st position (smallest) where 
            //      parr[pos] < val
            nPos = 0;
            while (nPos < nEnd && parr[nPos] >= val) { nPos++; }

            // Starting from nPos+1, move everything forward
            for (int i=nEnd; i> nPos;i--)
            {
                parr[i] = parr[i-1];
            }

            // Insert at nPos
            parr[nPos] = val;
            return 0;
		}

        template<typename T>
        static int insert_into_sorted_desc(T* parr, int nBegin, int nEnd, T val, int& nPos)
        {
            // Pre-requisite: parr is sorted desc (p[i] >= p[i+1], every i)
            // If the pre-requisite condition is not meet => the result will incorrect, 
            // This function does not validate pre-requisite condition.

            // Find the 1st position where val >= p[loc]
            nPos = nBegin;

            while (nPos < nEnd && (val < parr[nPos]))
            {
                nPos++;
            }

            // Starting from nPos+1, move everything forward 1step
            for (int i=nEnd;i>nPos;i--)
            {
                parr[i] = parr[i-1];
            }

            // Insert 
            parr[nPos] = val;
            return 0;
        }

        template<typename T>
        static int remove_element(T* parr, int nBegin, int &nEnd, int removeIndex)
        {
            if (removeIndex >= nBegin && removeIndex < nEnd)
            {
                for (int i=removeIndex;i<nEnd-1;++1)
                {
                    parr[i]=parr[i+1];
                }
                nEnd--;
                return 0;
            }
            return 1;
        }

        template<typename T>
        static int remove_element(T* parr, T* parr2, int nBegin, int& nEnd, int removeIndex)
        {
            if (removeIndex >= nBegin && removeIndex < nEnd)
            {
                for (int i=removeIndex;i<nEnd-1;++i)
                {
                    parr[i]=parr[i+1];
                    parr2[i] = parr2[i+1];
                }

                nEnd--;
                return 0;
            }
            return 1;
        }
        
        template<typename T>
        static int remove_elements(T* parr, int nBegin, int &nEnd, int* prm_indexes, int nRemoveStart, int nRemoveEnd)
        {
            // Validate 
            for (int i=nRemoveStart;i<nRemoveEnd;++i)
            {
                if (prm_indexes[i] < nBegin || prm_indexes[i] >= nEnd)
                {
                    // Invalid data
                    return 1;
                }
            }

            int nRemove = nRemoveEnd - nRemoveStart;
            int* premove = (int*)malloc(sizeof(int)*nRemove);

            memcpy(premove, prm_indexes + nRemoveStart, nRemove*sizeof(int));
            std::sort(premove, premove+nRemove);

            // Remove from largest position first, then go on.
            for (int i=nRemove-1;i>=0;i--)
            {
                for (int j=premove[i];j<nEnd;j++)
                {
                    parr[j] = parr[j+1];
                }
                nEnd--;
            }

            return 0;
        }

		template<typename T>
		static int remove_elements(T* parr, T* parr2, int nBegin, int &nEnd, int* prm_indexes, int nRemoveStart, int nRemoveEnd)
		{
			// Validate 
			for (int i = nRemoveStart; i < nRemoveEnd; ++i)
			{
				if (prm_indexes[i] < nBegin || prm_indexes[i] >= nEnd)
				{
					// Invalid data
					return 1;
				}
			}

			int nRemove = nRemoveEnd - nRemoveStart;
			int* premove = (int*)malloc(sizeof(int)*nRemove);

			memcpy(premove, prm_indexes + nRemoveStart, nRemove * sizeof(int));
			std::sort(premove, premove + nRemove);

			// Remove from largest position first, then go on.
			for (int i = nRemove - 1; i >= 0; i--)
			{
				for (int j = premove[i]; j < nEnd; j++)
				{
					parr[j] = parr[j + 1];
					parr2[j] = parr2[j + 1];
				}

				nEnd--;
			}

			return 0;
		}
	};
};


#endif