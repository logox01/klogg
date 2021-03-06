/*
 * Copyright (C) 2016 -- 2019 Anton Filimonov and other contributors
 *
 * This file is part of klogg.
 *
 * klogg is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * klogg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with klogg.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef KLOGG_FAVORITEFILES_H
#define KLOGG_FAVORITEFILES_H

#include <QString>
#include <vector>

#include "persistable.h"

// Manage the list of recently opened files
class FavoriteFiles final : public Persistable<FavoriteFiles, session_settings>
{
  public:
    struct File {
        explicit File(const QString& path);

        QString fullPath;
        QString fullPathNative;
        QString displayName;
    };

    struct FullPathComparator {
        FullPathComparator( const QString& path )
            : fullPath( path )
        {
        }

        bool operator()( const File& f ) const
        {
            return f.fullPath == fullPath;
        }

        QString fullPath;
    };

    struct FullPathNativeComparator {
        FullPathNativeComparator( const QString& path )
            : fullPathNative( path )
        {
        }

        bool operator()( const File& f ) const
        {
            return f.fullPathNative == fullPathNative;
        }

        QString fullPathNative;
    };

    void add( const QString& path );
    void remove( const QString& path );

    std::vector<File> favorites() const;

    // Reads/writes the current config in the QSettings object passed
    void saveToStorage( QSettings& settings ) const;
    void retrieveFromStorage( QSettings& settings );

  private:
    std::vector<File> files_;
};

#endif // KLOGG_FAVORITEFILES_H
