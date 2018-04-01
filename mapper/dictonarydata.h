#ifndef DICTONARYDATA_H
#define DICTONARYDATA_H

#include <QObject>
#include <QVector>

class Example
{
public:
    Example();
    ~Example();

    void setText(const QString& text_)        { text = text_; }
    void addTranslation(const QString& tr_)   { translations << tr_; }

    void showExample(); // Show a usage example.
private:
    QString text;               // Text of an example.
    QStringList translations;   // Translations of the text of an example.
};

class Translation
{
public:
    Translation();
    ~Translation();

    void setText(const QString& text_)        { text = text_; }
    void setPartOfSpeech(const QString& pos_) { pos = pos_; }
    void setAspect(const QString& asp_)       { asp = asp_; }
    void setNounForm(const QString& num_)     { num = num_; }
    void setGender(const QString& gen_)       { gen = gen_; }
    void addSynonym(const QString& syn_)      { synonyms << syn_; }
    void addMeaning(const QString& mean_)     { meanings << mean_; }
    void addExample(Example& example_)  { examples.push_back(example_); }

    QString getText()const{return text;}

    void showTranslation(QString &str); // Show a translation.
private:
    QString text;   // Translation text.
    QString pos;    // Part of speech.
    QString asp;    // The aspect of a verb.
    QString num;    // The form of a noun and its variations: plural, etc.
    QString gen;    // Gender.
    QStringList synonyms;// Synonyms.
    QStringList meanings;   // Meanings.
    QVector<Example> examples;// Usage examples.
};

class DictionaryEntry
{
public:
    DictionaryEntry();
    ~DictionaryEntry();

    void setText(const QString& text_)            { text = text_; }
    void setTranscription(const QString& ts_)     { ts = ts_; }
    void setPartOfSpeech(const QString& pos_)     { pos = pos_; }
    void addTranslation(const Translation& tr_)   { translations.push_back(tr_); }

    void showEntry(QString &txt_stream);   // Show a dictionary entry.


    QString getText() const;

    static QVector<DictionaryEntry> make_from_string(const QString & json_text);

    QString getTranscription() const;

    QVector<Translation> getTranslations() const;

private:
    QString text;   // A word which you wanted to find a dictionary entry for.
    QString ts;     // Transcription.
    QString pos;    // Part of speech.
    QVector<Translation> translations; // Translations.
};

#endif // DICTONARYDATA_H
