#ifndef COMMON_H
#define COMMON_H

//对应tree 表中的属性
enum DBTreeKey {
    DB_TREE_NODEID = Qt::UserRole + 100,
    DB_TREE_PARENT_NODEID,
    DB_TREE_ERR_ID,
    DB_TREE_ERR_DESC,
    DB_TREE_RULE_ID,
    DB_TREE_ALARM_ID,
};

#endif // COMMON_H
