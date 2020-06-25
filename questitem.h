#ifndef QUESTITEM_H
#define QUESTITEM_H

#include "item.h"


class QuestItem : public Item
{
public:

    QuestItem(QString name, QString description);
    bool useOnce() const override;
    void consume(Hero *hero) const override{};
};

#endif // QUESTITEM_H
