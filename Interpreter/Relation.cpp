/*======================================================================
 
--------------------------RELATION DEFINITIONS--------------------------
 
======================================================================*/

// Include file
#include "Relation.h"

// Setup namespace
using namespace std;

//======================================================================

// Define the relation constructor
Relation::Relation(string name)
{
    this->name = name;
}

//======================================================================

// Define the select function
Relation Relation::select(int index, string value)
{
    Relation relation = Relation(this->name);
    relation.schemes_list = this->schemes_list;
    
    for(Tuple tuple : this->tuples)
    {
        if(tuple.at(index) == value)
        {
            relation.tuples.insert(tuple);
        }
    }
    
    return relation;
}

//======================================================================

// Define the select compare function
Relation Relation::selectCompare(int index_I, int index_II)
{
    Relation relation = Relation(this->name);
    relation.schemes_list = this->schemes_list;
    
    for(Tuple tuple : this->tuples)
    {
        if(tuple.at(index_I) == tuple.at(index_II))
        {
            relation.tuples.insert(tuple);
        }
    }
    return relation;
}

//======================================================================

// Define the project function
Relation Relation::project(vector<int> indices)
{
    Relation relation = Relation(this->name);
    
    for(int i = 0; i < indices.size(); ++i)
    {
        relation.schemes_list.push_back(this->schemes_list.at(indices[i]));
    }
    
    for(Tuple tuple : this->tuples)
    {
        Tuple new_tuple;
        for(int i = 0; i < indices.size(); ++i)
        {
            new_tuple.push_back(tuple.at(indices[i]));
        }
        relation.tuples.insert(new_tuple);
    }
    
    return relation;
}

//======================================================================

// Define the rename function
Relation Relation::rename(vector<string> names)
{
    Relation relation = Relation(this->name);
    relation.tuples = this->tuples;
    
    for(int i = 0; i < names.size(); ++i)
    {
        relation.schemes_list.push_back(names[i]);
    }
    
    return relation;
}

//======================================================================

// Define the same attributes function
vector<pair<int, int>> Relation::sameAttributes(Relation relation_II)
{
    vector<pair<int, int>> same_attributes;
    
    for(int i = 0; i < this->schemes_list.size(); ++i)
    {
        for(int j = 0; j < relation_II.schemes_list.size(); ++j)
        {
            if(this->schemes_list[i] == relation_II.schemes_list[j])
            {
                same_attributes.push_back({i,j});
            }
        }
    }
    
    return same_attributes;
}

//======================================================================

// Define the can join function
bool Relation::canJoin(Tuple tuple_I, Tuple tuple_II, vector<pair<int, int>> same_attributes)
{
    bool join_check = false;
    
    for(auto match : same_attributes)
    {
        if(tuple_I.at(match.first) == tuple_II.at(match.second))
        {
            join_check = true;
        }
        
        else
        {
            join_check = false;
            return join_check;
        }
    }
    
    return join_check;
}

//======================================================================

// Define the make union function
string Relation::makeUnion(Relation relation_II)
{
    stringstream ss;
    
    for(Tuple new_tuple : relation_II.tuples)
    {
        pair<set<Tuple>::iterator, bool> iterator = this->tuples.insert(new_tuple);
        if(iterator.second == true)
        {
            ss << "\n ";
            for(int i = 0; i < this->schemes_list.size(); ++i)
            {
                ss << " " << this->schemes_list[i] << "=" << new_tuple[i];
            }
        }
    }
    
    ss << "\n";
    return ss.str();
}

//======================================================================

// Define the join function
Relation Relation::join(Relation relation_II)
{
    Relation joining = Relation("joining");
    joining.schemes_list = joinScheme(relation_II);
    vector<pair<int, int>> common_attributes = sameAttributes(relation_II);
    
    for(Tuple new_tuple : this->tuples)
    {
        for(Tuple new_tuple_II : relation_II.tuples)
        {
            if(common_attributes.size() > 0)
            {
                if(canJoin(new_tuple, new_tuple_II, common_attributes) == true)
                {
                    Tuple tuple_join = joinTuples(new_tuple, new_tuple_II, common_attributes);
                    joining.tuples.insert(tuple_join);
                }
            }
            
            else
            {
                Tuple tuple_product = makeProduct(new_tuple, new_tuple_II);
                joining.tuples.insert(tuple_product);
            }
        }
    }
    
    return joining;
}

//======================================================================

// Define the join scheme function
Scheme Relation::joinScheme(Relation relation_II)
{
    Scheme scheme;
    
    for(auto add : this->schemes_list)
    {
        scheme.push_back(add);
    }
    
    for(auto check : this->schemes_list)
    {
        for(auto add_II : relation_II.schemes_list)
        {
            if(find(scheme.begin(), scheme.end(), add_II) == scheme.end())
            {
                scheme.push_back(add_II);
            }
        }
    }
    
    return scheme;
}

//======================================================================

// Define the join tuples function
Tuple Relation::joinTuples(Tuple tuple_I, Tuple tuple_II, vector<pair<int, int>> same_attributes)
{
    Tuple new_tuple;
    
    for(auto add : tuple_I)
    {
        new_tuple.push_back(add);
    }
    
    for(int i = 0; i < tuple_II.size(); ++i)
    {
        bool same_check = false;
        for(auto match : same_attributes)
        {
            if(i == match.second)
            {
                same_check = true;
            }
        }
        
        if(same_check == false)
        {
            new_tuple.push_back(tuple_II[i]);
        }
        
    }
    
    return new_tuple;
}

//======================================================================

// Define the make prdocut function
Tuple Relation::makeProduct(Tuple tuple_I, Tuple tuple_II)
{
    Tuple new_tuple;
    for(auto product_I : tuple_I)
    {
        new_tuple.push_back(product_I);
    }
    
    for(auto product_II : tuple_II)
    {
        new_tuple.push_back(product_II);
    }
    
    return new_tuple;
}

//======================================================================

// Define the to string function
string Relation::toString()
{
    stringstream ss;
    
    for(auto tuple : this->tuples)
    {
        if(tuple.empty() == false)
        {
            ss << " ";
            for(int i = 0; i < this->schemes_list.size(); ++i)
            {
                ss << " " << schemes_list[i] << "=" << tuple[i];
            }
            ss << endl;
        }
    }

    return ss.str();
}

//======================================================================

// Define the relation destructor
Relation::~Relation(){}

//======================================================================