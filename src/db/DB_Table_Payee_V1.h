// -*- C++ -*-
//=============================================================================
/**
 *      Copyright (c) 2013 Guan Lisheng (guanlisheng@gmail.com)
 *
 *      @file
 *
 *      @author [sqlite2cpp.py]
 *
 *      @brief
 *
 *      Revision History:
 *          AUTO GENERATED at 2013-10-29 15:19:18.567932.
 *          DO NOT EDIT!
 */
//=============================================================================

#ifndef DB_TABLE_PAYEE_V1_H
#define DB_TABLE_PAYEE_V1_H

#include "DB_Table.h"

struct DB_Table_PAYEE_V1 : public DB_Table
{
    struct Data;
    typedef DB_Table_PAYEE_V1 Self;
    /** A List container to hold Data records for the table*/
    typedef std::vector<Self::Data> Data_Set;
    /** A List container to hold Data record pointers for the table*/
    typedef std::vector<Self::Data*> Cache;
    Cache cache_;
    ~DB_Table_PAYEE_V1() 
    {
        destroy_cache();
    }
    
    /** Removes all table data stored in memory*/ 
    void destroy_cache()
    {
        std::for_each(cache_.begin(), cache_.end(), std::mem_fun(&Data::destroy));
        cache_.clear();
    }

    /** Creates the database table if the table does not exist*/
    bool ensure(wxSQLite3Database* db)
    {
        if (exists(db)) return true;
        destroy_cache();

        try
        {
            db->ExecuteUpdate("CREATE TABLE PAYEE_V1(PAYEEID integer primary key, PAYEENAME TEXT COLLATE NOCASE NOT NULL UNIQUE, CATEGID integer, SUBCATEGID integer)");
        }
        catch(const wxSQLite3Exception &e) 
        { 
            wxLogError("PAYEE_V1: Exception %s", e.GetMessage().c_str());
            return false;
        }

        return true;
    }

    struct PAYEEID : public DB_Column<int>
    { 
        static wxString name() { return "PAYEEID"; } 
        PAYEEID(const int &v, OP op = EQUAL): DB_Column<int>(v, op) {}
    };
    struct PAYEENAME : public DB_Column<wxString>
    { 
        static wxString name() { return "PAYEENAME"; } 
        PAYEENAME(const wxString &v, OP op = EQUAL): DB_Column<wxString>(v, op) {}
    };
    struct CATEGID : public DB_Column<int>
    { 
        static wxString name() { return "CATEGID"; } 
        CATEGID(const int &v, OP op = EQUAL): DB_Column<int>(v, op) {}
    };
    struct SUBCATEGID : public DB_Column<int>
    { 
        static wxString name() { return "SUBCATEGID"; } 
        SUBCATEGID(const int &v, OP op = EQUAL): DB_Column<int>(v, op) {}
    };
    typedef PAYEEID PRIMARY;
    enum COLUMN
    {
        COL_PAYEEID = 0
        , COL_PAYEENAME = 1
        , COL_CATEGID = 2
        , COL_SUBCATEGID = 3
    };

    /** Returns the column name as a string*/
    wxString column_to_name(COLUMN col) const
    {
        switch(col)
        {
            case COL_PAYEEID: return "PAYEEID";
            case COL_PAYEENAME: return "PAYEENAME";
            case COL_CATEGID: return "CATEGID";
            case COL_SUBCATEGID: return "SUBCATEGID";
            default: break;
        }
        
        return "UNKNOWN";
    }

    /** Returns the comumn number from the given column name*/
    COLUMN name_to_column(const wxString& name) const
    {
        if ("PAYEEID" == name) return COL_PAYEEID;
        else if ("PAYEENAME" == name) return COL_PAYEENAME;
        else if ("CATEGID" == name) return COL_CATEGID;
        else if ("SUBCATEGID" == name) return COL_SUBCATEGID;

        return COLUMN(-1);
    }
    
    /** Contains the table record for the table*/
    struct Data
    {
        friend struct DB_Table_PAYEE_V1;
        Self* view_;
    
        int PAYEEID;//  primay key
        wxString PAYEENAME;
        int CATEGID;
        int SUBCATEGID;
        int id() const { return PAYEEID; }
        void id(int id) { PAYEEID = id; }
        bool operator < (const Data& r) const
        {
            return this->id() < r.id();
        }
        bool operator < (const Data* r) const
        {
            return this->id() < r->id();
        }

        Data(Self* view = 0) 
        {
            view_ = view;
        
            PAYEEID = -1;
            CATEGID = -1;
            SUBCATEGID = -1;
        }

        Data(wxSQLite3ResultSet& q, Self* view = 0)
        {
            view_ = view;
        
            PAYEEID = q.GetInt("PAYEEID");
            PAYEENAME = q.GetString("PAYEENAME");
            CATEGID = q.GetInt("CATEGID");
            SUBCATEGID = q.GetInt("SUBCATEGID");
        }

        wxString to_json() const
        {
            json::Object o;
            this->to_json(o);
            std::stringstream ss;
            json::Writer::Write(o, ss);
            return ss.str();
        }
        
        int to_json(json::Object& o) const
        {
            o["PAYEEID"] = json::Number(this->PAYEEID);
            o["PAYEENAME"] = json::String(this->PAYEENAME.ToStdString());
            o["CATEGID"] = json::Number(this->CATEGID);
            o["SUBCATEGID"] = json::Number(this->SUBCATEGID);
            return 0;
        }

        bool save(wxSQLite3Database* db)
        {
            if (!view_ || !db) 
            {
                wxLogError("can not save");
                return false;
            }

            return view_->save(this, db);
        }

        bool remove(wxSQLite3Database* db)
        {
            if (!view_ || !db) 
            {
                wxLogError("can not remove");
                return false;
            }
            
            return view_->remove(this, db);
        }

        void destroy() { delete this; }
    };

    enum
    {
        NUM_COLUMNS = 4
    };

    size_t num_columns() const { return NUM_COLUMNS; }

    /** Name of the table*/    
    wxString name() const { return "PAYEE_V1"; }

    DB_Table_PAYEE_V1() 
    {
        query_ = "SELECT PAYEEID, PAYEENAME, CATEGID, SUBCATEGID FROM PAYEE_V1 ";
    }

    /** Create a new data record*/
    Self::Data* create()
    {
        Self::Data* entity = new Self::Data(this);
        cache_.push_back(entity);
        return entity;
    }
    
    /** Create a copy of the data record*/
    Self::Data* clone(const Data* e)
    {
        Self::Data* entity = create();
        *entity = *e;
        entity->id(-1);
        return entity;
    }

    /** Save the data record to the database, either create new or update the existing record*/
    bool save(Self::Data* entity, wxSQLite3Database* db)
    {
        wxString sql = wxEmptyString;
        if (entity->id() < 0) //  new & insert
        {
            sql = "INSERT INTO PAYEE_V1(PAYEENAME, CATEGID, SUBCATEGID) VALUES(?, ?, ?)";
        }
        else
        {
            sql = "UPDATE PAYEE_V1 SET PAYEENAME = ?, CATEGID = ?, SUBCATEGID = ? WHERE PAYEEID = ?";
        }

        try
        {
            wxSQLite3Statement stmt = db->PrepareStatement(sql);

            stmt.Bind(1, entity->PAYEENAME);
            stmt.Bind(2, entity->CATEGID);
            stmt.Bind(3, entity->SUBCATEGID);
            if (entity->id() > 0)
                stmt.Bind(4, entity->PAYEEID);

            wxLogDebug(stmt.GetSQL());
            stmt.ExecuteUpdate();
            stmt.Finalize();
        }
        catch(const wxSQLite3Exception &e) 
        { 
            wxLogError("PAYEE_V1: Exception %s, %s", e.GetMessage().c_str(), entity->to_json());
            return false;
        }

        if (entity->id() < 0) entity->id((db->GetLastRowId()).ToLong());
        return true;
    }

    bool remove(int id, wxSQLite3Database* db)
    {
        try
        {
            wxString sql = "DELETE FROM PAYEE_V1 WHERE PAYEEID = ?";
            wxSQLite3Statement stmt = db->PrepareStatement(sql);
            stmt.Bind(1, id);
            wxLogDebug(stmt.GetSQL());
            stmt.ExecuteUpdate();
            stmt.Finalize();

            Cache c;
            for(Cache::iterator it = cache_.begin(); it != cache_.end(); ++ it)
            {
                Self::Data* entity = *it;
                if (entity->id() == id) 
                    delete entity;
                else 
                    c.push_back(entity);
            }
            cache_.clear();
            cache_.swap(c);
        }
        catch(const wxSQLite3Exception &e) 
        { 
            wxLogError("PAYEE_V1: Exception %s", e.GetMessage().c_str());
            return false;
        }

        return true;
    }

    bool remove(Self::Data* entity, wxSQLite3Database* db)
    {
        if (remove(entity->id(), db))
        {
            entity->id(-1);
            return true;
        }

        return false;
    }

    
    Self::Data* get(int id, wxSQLite3Database* db)
    {
        if (id < 0) 
        {
            ++ skip_;
            wxLogDebug("%s :%d SKIP (hit %ld, miss %ld, skip %ld)", this->name(), id, this->hit_, this->miss_, this->skip_);
            return 0;
        }
        for(Cache::reverse_iterator it = cache_.rbegin(); it != cache_.rend(); ++ it)
        {
            Self::Data* entity = *it;
            if (entity->id() == id) 
            {
                ++ hit_;
                wxLogDebug("%s :%d HIT (hit %ld, miss %ld, skip %ld)", this->name(), id, this->hit_, this->miss_, this->skip_);
                return entity;
            }
        }
        
        ++ miss_;
        wxLogDebug("%s :%d MISS (hit %ld, miss %ld, skip %ld)", this->name(), id, this->hit_, this->miss_, this->skip_);
        Self::Data* entity = 0;
        wxString where = wxString::Format(" WHERE %s = ?", PRIMARY::name().c_str());
        try
        {
            wxSQLite3Statement stmt = db->PrepareStatement(this->query() + where);
            stmt.Bind(1, id);

            wxLogDebug(stmt.GetSQL());
            wxSQLite3ResultSet q = stmt.ExecuteQuery();
            if(q.NextRow())
            {
                entity = new Self::Data(q, this);
                cache_.push_back(entity);
            }
            stmt.Finalize();
        }
        catch(const wxSQLite3Exception &e) 
        { 
            wxLogError("%s: Exception %s", this->name().c_str(), e.GetMessage().c_str());
        }
        
        if (!entity) 
        {
            wxLogError("%s: %d not found", this->name().c_str(), id);
        }
 
        return entity;
    }

    /** Return a list of all the records in the database*/
    Data_Set all(wxSQLite3Database* db, COLUMN col = COLUMN(0), bool asc = true)
    {
        Data_Set result;
        try
        {
            wxSQLite3ResultSet q = db->ExecuteQuery(this->query() + " ORDER BY " + column_to_name(col) + " COLLATE NOCASE " + (asc ? " ASC " : " DESC ")
                + "," + PRIMARY::name());

            wxLogDebug(q.GetSQL());
            while(q.NextRow())
            {
                Self::Data entity(q, this);
                result.push_back(entity);
            }

            q.Finalize();
        }
        catch(const wxSQLite3Exception &e) 
        { 
            wxLogError("%s: Exception %s", this->name().c_str(), e.GetMessage().c_str());
        }

        return result;
    }

};
#endif //
