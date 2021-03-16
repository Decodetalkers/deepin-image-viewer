/*
 * Copyright (C) 2020 ~ 2021 Uniontech Software Technology Co., Ltd.
 *
 * Author:     LiuMingHang <liuminghang@uniontech.com>
 *
 * Maintainer: ZhangYong <ZhangYong@uniontech.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef IMAGEUTILS_LIBEXIF_H
#define IMAGEUTILS_LIBEXIF_H

#include "baseutils.h"
#include <libexif/exif-data.h>
#include <QDateTime>
#include <QFileInfo>
#include <QString>

#endif // IMAGEUTILS_LIBEXIF_H

namespace utils {

namespace image {

namespace libexif {

QString readExifTag(ExifData *ed, ExifIfd eid, ExifTag tag)
{
    ExifEntry *entry = exif_content_get_entry(ed->ifd[eid], tag);

    if (entry) {
        char buf[1024];
        exif_entry_get_value(entry, buf, sizeof(buf));

        if (*buf) {
            return QString(buf).trimmed();
        }
    }

    return QString();
}


QDateTime getCreateDateTime(const QString &path)
{
    ExifData *ed = exif_data_new_from_file(path.toUtf8().data());
    if (ed) {
        QDateTime dt = utils::base::stringToDateTime(
                           readExifTag(ed, EXIF_IFD_EXIF, EXIF_TAG_DATE_TIME_ORIGINAL));
        //Free the EXIF data
        exif_data_unref(ed);
        if (dt.isValid())
            return dt;
    }

    return QDateTime();
}
//LMH20201117 屏蔽没使用代码
//QSize size(const QString &path) {
//    ExifData *ed = exif_data_new_from_file(path.toUtf8().data());
//    if (ed) {
//        int w = readExifTag(ed, EXIF_IFD_EXIF, EXIF_TAG_IMAGE_WIDTH).toInt();
//        int h = readExifTag(ed, EXIF_IFD_EXIF, EXIF_TAG_IMAGE_LENGTH).toInt();
//        //Free the EXIF data
//        exif_data_unref(ed);
//        return QSize(w, h);
//    }
//    return QSize();
//}

//QString orientation(const QString &path)
//{
//    ExifData *ed = exif_data_new_from_file(path.toUtf8().data());
//    if (ed) {
//        QString ot = readExifTag(ed, EXIF_IFD_EXIF, EXIF_TAG_ORIENTATION);
//        //Free the EXIF data
//        exif_data_unref(ed);
//        return ot;
//    }
//    return QString();
//}

}  // namespace libexif

}  // namespace image

}  // namespace utils
