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


//对应rule 表中的属性
enum DBRuleKey {
    DB_RULE_RULEID = Qt::UserRole + 100,
    DB_RULE_ERR_DESC,
    DB_RULE_DETECT_TIP,
    DB_RULE_DEPAND_ERRID,
    DB_RULE_PARAMID,
    DB_RULE_JUDG,
    DB_RULE_ERR_REASON,
    DB_RULE_SUGGEST
};

#endif // COMMON_H
