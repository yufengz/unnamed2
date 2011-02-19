#ifndef NOTE_H
#define NOTE_H

#include "settings.h"

#include <QFileInfo>
#include <QFile>
#include <QTextCharFormat>

class Note : public QObject
{
	Q_OBJECT
public:
	enum Type
	{
		type_text,
		type_html,
		type_picture,
#ifdef NOTE_TODO_FORMAT
		type_todo,
#endif
#ifdef NOTE_XML_FORMAT
		type_xml,
#endif
	};
public:
	Note(const QFileInfo& fileinfo, Note::Type type_new);
	virtual ~Note();

	inline const QString& title() const { return _title; }
	inline const QString absolutePath() const { return file_info.absoluteFilePath(); }
	inline const QString fileName() const { return file_info.fileName(); }
	inline Type type() const { return _type; }

	virtual QWidget* widget() = 0;

	void updateTitle(bool show_extensions);

	virtual void load() = 0; //Reading note's content
	virtual void save(bool forced = false) = 0; //Saving note's content

	void rename(const QString& new_name);
	void move(const QString& new_dir);

	virtual void copy() const = 0; //Coping note's content to clipboard
	virtual bool find(const QString& text, bool next=false); //Searching text in a note's content

	virtual void setSelFormat(const QTextCharFormat& format)
	{
		Q_UNUSED(format)
	}
	virtual QTextCharFormat getSelFormat() const
	{
		return QTextCharFormat();
	}
	virtual void retranslate(const QLocale& locale)
	{
		Q_UNUSED(locale)
	}
private:
	Type _type;
	QString _title;
	QFileInfo file_info;
protected:
	QFile file;
	//
	bool content_changed;
private slots:
	void contentChanged();
};

#endif // NOTE_H
