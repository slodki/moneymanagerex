﻿// -*- C++ -*-
/** @file
 * @brief     CRUD implementation for INFOTABLE SQLite table
 * @warning   Auto generated with sqlite2cpp.py script. DO NOT EDIT!
 * @copyright © 2013-2018 Guan Lisheng
 * @copyright © 2017-2018 Stefano Giorgio
 * @author    Guan Lisheng (guanlisheng@gmail.com)
 * @author    Stefano Giorgio (stef145g)
 * @author    Tomasz Słodkowicz
 * @date      2019-04-30 03:41:33.533622
 */
#pragma once

#include "Table.h"

struct DB_Table_INFOTABLE : public DB_Table
{
    struct Data;
    typedef DB_Table_INFOTABLE Self;

    /** A container to hold list of Data records for the table*/
    struct Data_Set : public std::vector<Self::Data>
    {
        /** Return the data records as a json array string */
        wxString to_json() const
        {
            StringBuffer json_buffer(nullptr);
            PrettyWriter<StringBuffer> json_writer(json_buffer, nullptr);

            json_writer.StartArray();
            for (const auto & item: *this)
            {
                json_writer.StartObject();
                item.as_json(json_writer);
                json_writer.EndObject();
            }
            json_writer.EndArray();

            return json_buffer.GetString();
        }
    };

    /** A container to hold a list of Data record pointers for the table in memory*/
    typedef std::vector<Self::Data*> Cache;
    typedef std::map<int, Self::Data*> Index_By_Id;
    Cache cache_;
    Index_By_Id index_by_id_;
    Data* fake_; // in case the entity not found

    /** Destructor: clears any data records stored in memory */
    ~DB_Table_INFOTABLE()
    {
        delete fake_;
        destroy_cache();
    }

    /** Removes all records stored in memory (cache) for the table*/
    void destroy_cache()
    {
        std::for_each(cache_.begin(), cache_.end(), std::mem_fun(&Data::destroy));
        cache_.clear();
        index_by_id_.clear(); // no memory release since it just stores pointer and the according objects are in cache
    }

    /** Creates the database table if the table does not exist*/
    bool ensure(wxSQLite3Database* db)
    {
        if (!exists(db))
        {
            try
            {
                db->ExecuteUpdate("CREATE TABLE INFOTABLE(INFOID integer not null primary key, INFONAME TEXT COLLATE NOCASE NOT NULL UNIQUE, INFOVALUE TEXT NOT NULL)");
                ensure_data(db);
            }
            catch(const wxSQLite3Exception &e)
            {
                wxLogError("INFOTABLE: Exception %s", e.GetMessage().c_str());
                return false;
            }
        }

        ensure_index(db);

        return true;
    }

    bool ensure_index(wxSQLite3Database* db)
    {
        try
        {
            db->ExecuteUpdate("CREATE INDEX IF NOT EXISTS IDX_INFOTABLE_INFONAME ON INFOTABLE(INFONAME)");
        }
        catch(const wxSQLite3Exception &e)
        {
            wxLogError("INFOTABLE: Exception %s", e.GetMessage().c_str());
            return false;
        }

        return true;
    }

    void ensure_data(wxSQLite3Database* db)
    {
        db->Begin();
        db->ExecuteUpdate("INSERT INTO INFOTABLE VALUES ('1', 'DATAVERSION', '3')");
        db->Commit();
    }
    
    struct INFOID : public DB_Column<int>
    {
        static wxString name() { return "INFOID"; }
        explicit INFOID(const int &v, OP op = EQUAL): DB_Column<int>(v, op) {}
    };
    
    struct INFONAME : public DB_Column<wxString>
    {
        static wxString name() { return "INFONAME"; }
        explicit INFONAME(const wxString &v, OP op = EQUAL): DB_Column<wxString>(v, op) {}
    };
    
    struct INFOVALUE : public DB_Column<wxString>
    {
        static wxString name() { return "INFOVALUE"; }
        explicit INFOVALUE(const wxString &v, OP op = EQUAL): DB_Column<wxString>(v, op) {}
    };
    
    typedef INFOID PRIMARY;
    enum COLUMN
    {
        COL_INFOID = 0
        , COL_INFONAME = 1
        , COL_INFOVALUE = 2
        , COL_UNKNOWN = -1
    };

    /** Returns the column name as a string*/
    static wxString column_to_name(COLUMN col)
    {
        switch(col)
        {
            case COL_INFOID: return "INFOID";
            case COL_INFONAME: return "INFONAME";
            case COL_INFOVALUE: return "INFOVALUE";
            default: break;
        }

        return "UNKNOWN";
    }

    /** Returns the column number from the given column name*/
    static COLUMN name_to_column(const wxString& name)
    {
        if ("INFOID" == name) return COL_INFOID;
        else if ("INFONAME" == name) return COL_INFONAME;
        else if ("INFOVALUE" == name) return COL_INFOVALUE;

        return COL_UNKNOWN;
    }
    
    /** Data is a single record in the database table*/
    struct Data
    {
        friend struct DB_Table_INFOTABLE;
        /** This is a instance pointer to itself in memory. */
        Self* table_;
    
        int INFOID; // primary key
        wxString INFONAME;
        wxString INFOVALUE;

        int id() const
        {
            return INFOID;
        }

        void id(int id)
        {
            INFOID = id;
        }

        bool operator < (const Data& r) const
        {
            return id() < r.id();
        }

        bool operator < (const Data* r) const
        {
            return id() < r->id();
        }

        explicit Data(Self* table = nullptr)
        {
            table_ = table;
        
            INFOID = -1;
        }

        explicit Data(wxSQLite3ResultSet& q, Self* table = nullptr)
        {
            table_ = table;
        
            INFOID = q.GetInt(0);
            INFONAME = q.GetString(1);
            INFOVALUE = q.GetString(2);
        }

        Data& operator=(const Data& other)
        {
            if (this == &other) return *this;

            INFOID = other.INFOID;
            INFONAME = other.INFONAME;
            INFOVALUE = other.INFOVALUE;
            return *this;
        }


        bool match(const Self::INFOID &in) const
        {
            return this->INFOID == in.v_;
        }

        bool match(const Self::INFONAME &in) const
        {
            return this->INFONAME.CmpNoCase(in.v_) == 0;
        }

        bool match(const Self::INFOVALUE &in) const
        {
            return this->INFOVALUE.CmpNoCase(in.v_) == 0;
        }

        /** Return the data record as a json string */
        wxString to_json() const
        {
            StringBuffer json_buffer(nullptr);
            PrettyWriter<StringBuffer> json_writer(json_buffer, nullptr);

            json_writer.StartObject();
            as_json(json_writer);
            json_writer.EndObject();

            return json_buffer.GetString();
        }

        /** Add the field data as json key:value pairs */
        void as_json(PrettyWriter<StringBuffer>& json_writer) const
        {
            json_writer.Key("INFOID");
            json_writer.Int(this->INFOID);
            json_writer.Key("INFONAME");
            json_writer.String(this->INFONAME.c_str());
            json_writer.Key("INFOVALUE");
            json_writer.String(this->INFOVALUE.c_str());
        }

        row_t to_row_t() const
        {
            row_t row;
            row(L"INFOID") = INFOID;
            row(L"INFONAME") = INFONAME;
            row(L"INFOVALUE") = INFOVALUE;
            return row;
        }

        void to_template(html_template& t) const
        {
            t(L"INFOID") = INFOID;
            t(L"INFONAME") = INFONAME;
            t(L"INFOVALUE") = INFOVALUE;
        }

        /** Save the record instance in memory to the database. */
        bool save(wxSQLite3Database* db)
        {
            if (db && db->IsReadOnly()) return false;
            if (!table_ || !db)
            {
                wxLogError("can not save INFOTABLE");
                return false;
            }

            return table_->save(this, db);
        }

        /** Remove the record instance from memory and the database. */
        bool remove(wxSQLite3Database* db)
        {
            if (!table_ || !db)
            {
                wxLogError("can not remove INFOTABLE");
                return false;
            }

            return table_->remove(this, db);
        }

        void destroy()
        {
            delete this;
        }
    };

    enum
    {
        NUM_COLUMNS = 3
    };

    size_t num_columns() const { return NUM_COLUMNS; }

    /** Name of the table */
    wxString name() const { return "INFOTABLE"; }

    DB_Table_INFOTABLE() : fake_(new Data())
    {
        query_ = "SELECT INFOID, INFONAME, INFOVALUE FROM INFOTABLE ";
    }

    /** Create a new Data record and add to memory table (cache) */
    Self::Data* create()
    {
        Self::Data* entity = new Self::Data(this);
        cache_.push_back(entity);
        return entity;
    }

    /** Create a copy of the Data record and add to memory table (cache) */
    Self::Data* clone(const Data* e)
    {
        Self::Data* entity = create();
        *entity = *e;
        entity->id(-1);
        return entity;
    }

    /**
    * Saves the Data record to the database table.
    * Either create a new record or update the existing record.
    * Remove old record from the memory table (cache)
    */
    bool save(Self::Data* entity, wxSQLite3Database* db)
    {
        wxString sql = wxEmptyString;
        if (entity->id() <= 0) //  new & insert
        {
            sql = "INSERT INTO INFOTABLE(INFONAME, INFOVALUE) VALUES(?, ?)";
        }
        else
        {
            sql = "UPDATE INFOTABLE SET INFONAME = ?, INFOVALUE = ? WHERE INFOID = ?";
        }

        try
        {
            wxSQLite3Statement stmt = db->PrepareStatement(sql);

            stmt.Bind(1, entity->INFONAME);
            stmt.Bind(2, entity->INFOVALUE);
            if (entity->id() > 0)
                stmt.Bind(3, entity->INFOID);

            stmt.ExecuteUpdate();
            stmt.Finalize();

            if (entity->id() > 0) // existent
            {
                for(Cache::iterator it = cache_.begin(); it != cache_.end(); ++ it)
                {
                    Self::Data* e = *it;
                    if (e->id() == entity->id())
                        *e = *entity;  // in-place update
                }
            }
        }
        catch(const wxSQLite3Exception &e)
        {
            wxLogError("INFOTABLE: Exception %s, %s", e.GetMessage().c_str(), entity->to_json());
            return false;
        }

        if (entity->id() <= 0)
        {
            entity->id((db->GetLastRowId()).ToLong());
            index_by_id_.insert(std::make_pair(entity->id(), entity));
        }
        return true;
    }

    /** Remove the Data record from the database and the memory table (cache) */
    bool remove(int id, wxSQLite3Database* db)
    {
        if (id <= 0) return false;
        try
        {
            wxString sql = "DELETE FROM INFOTABLE WHERE INFOID = ?";
            wxSQLite3Statement stmt = db->PrepareStatement(sql);
            stmt.Bind(1, id);
            stmt.ExecuteUpdate();
            stmt.Finalize();

            Cache c;
            for(Cache::iterator it = cache_.begin(); it != cache_.end(); ++ it)
            {
                Self::Data* entity = *it;
                if (entity->id() == id)
                {
                    index_by_id_.erase(entity->id());
                    delete entity;
                }
                else
                {
                    c.push_back(entity);
                }
            }
            cache_.clear();
            cache_.swap(c);
        }
        catch(const wxSQLite3Exception &e)
        {
            wxLogError("INFOTABLE: Exception %s", e.GetMessage().c_str());
            return false;
        }

        return true;
    }

    /** Remove the Data record from the database and the memory table (cache) */
    bool remove(Self::Data* entity, wxSQLite3Database* db)
    {
        if (remove(entity->id(), db))
        {
            entity->id(-1);
            return true;
        }

        return false;
    }

    template<typename... Args>
    Self::Data* get_one(const Args& ... args)
    {
        for (Index_By_Id::iterator it = index_by_id_.begin(); it != index_by_id_.end(); ++ it)
        {
            Self::Data* item = it->second;
            if (item->id() > 0 && match(item, args...))
            {
                ++ hit_;
                return item;
            }
        }

        ++ miss_;

        return nullptr;
    }

    /**
    * Search the memory table (Cache) for the data record.
    * If not found in memory, search the database and update the cache.
    */
    Self::Data* get(int id, wxSQLite3Database* db)
    {
        if (id <= 0)
        {
            ++ skip_;
            return nullptr;
        }

        Index_By_Id::iterator it = index_by_id_.find(id);
        if (it != index_by_id_.end())
        {
            ++ hit_;
            return it->second;
        }

        ++ miss_;
        Self::Data* entity = nullptr;
        wxString where = wxString::Format(" WHERE %s = ?", PRIMARY::name().c_str());
        try
        {
            wxSQLite3Statement stmt = db->PrepareStatement(query() + where);
            stmt.Bind(1, id);

            wxSQLite3ResultSet q = stmt.ExecuteQuery();
            if(q.NextRow())
            {
                entity = new Self::Data(q, this);
                cache_.push_back(entity);
                index_by_id_.insert(std::make_pair(id, entity));
            }
            stmt.Finalize();
        }
        catch(const wxSQLite3Exception &e)
        {
            wxLogError("%s: Exception %s", name().c_str(), e.GetMessage().c_str());
        }

        if (!entity)
        {
            entity = fake_;
            // wxLogError("%s: %d not found", name().c_str(), id);
        }

        return entity;
    }

    /**
    * Return a list of Data records (Data_Set) derived directly from the database.
    * The Data_Set is sorted based on the column number.
    */
    const Data_Set all(wxSQLite3Database* db, COLUMN col = COLUMN(0), bool asc = true)
    {
        Data_Set result;
        try
        {
            wxSQLite3ResultSet q = db->ExecuteQuery(col == COLUMN(0) ? query() : query() + " ORDER BY " + column_to_name(col) + " COLLATE NOCASE " + (asc ? " ASC " : " DESC "));

            while(q.NextRow())
            {
                Self::Data entity(q, this);
                result.push_back(std::move(entity));
            }

            q.Finalize();
        }
        catch(const wxSQLite3Exception &e)
        {
            wxLogError("%s: Exception %s", name().c_str(), e.GetMessage().c_str());
        }

        return result;
    }
};

