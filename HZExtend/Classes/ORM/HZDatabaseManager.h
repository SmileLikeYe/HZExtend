//
//  HZDatabaseManager.h
//  HZORM <https://github.com/GeniusBrother/HZORM>
//
//  Created by GeniusBrother on 16/12/8.
//  Copyright (c) 2016 GeniusBrother. All rights reserved.
//

#import <Foundation/Foundation.h>

#define HZDBManager [HZDatabaseManager sharedManager]

NS_ASSUME_NONNULL_BEGIN
typedef int(^HZDBExecuteStatementsCallbackBlock)(NSDictionary *resultsDictionary);

/**
 Responsible for the database operation.
 */
@interface HZDatabaseManager : NSObject

/** The path of database. */
@property(nonatomic, copy, nullable) NSString *dbPath;

/**
 Returns global HZDatabaseManager instance.
 
 @return HZDatabaseManager shared instance
 */
+ (instancetype)sharedManager;

/**
 Executes single update statement.
 This method executes a single SQL update statement (i.e. any SQL that does not return results, such as `UPDATE`, `INSERT`, or `DELETE`. This method employs [`sqlite3_prepare_v2`](http://sqlite.org/c3ref/prepare.html) and [`sqlite3_bind`](http://sqlite.org/c3ref/bind_blob.html) binding any `?` placeholders in the SQL with the optional list of parameters.
 
 The optional values provided to this method should be objects (e.g. `NSString`, `NSNumber`, `NSNull`, `NSDate`, and `NSData` objects), not fundamental data types (e.g. `int`, `long`, `NSInteger`, etc.). This method automatically handles the aforementioned object types, and all other object types will be interpreted as text values using the object's `description` method.
 
 @param sql The SQL to be performed, with optional `?` placeholders.
 @param data A `NSArray` of objects to be used when binding values to the `?` placeholders in the SQL statement.
 
 @return `YES` upon success; `NO` upon failure.
 */
- (BOOL)executeUpdate:(NSString *)sql withParams:(nullable NSArray *)data;

/** 
 Executes select statement.
 
 @param sql The SELECT statement to be performed, with optional `?` placeholders.
 @param arguments A `NSArray` of objects to be used when binding values to the `?` placeholders in the SQL statement.
 
 @return A `NSArray` for the result set upon success; `nil` upon failure.
 */
- (nullable NSArray *)executeQuery:(NSString *)sql withParams:(nullable NSArray *)data;

/** 
 Execute multiple SQL statements with callback handler.
 
 This executes a series of SQL statements that are combined in a single string (e.g. the SQL generated by the `sqlite3` command line `.dump` command). This accepts no value parameters, but rather simply expects a single string with multiple SQL statements, each terminated with a semicolon. This uses `sqlite3_exec`.
 
 @param sql       The SQL to be performed.
 @param block     A block that will be called for any result sets returned by any SQL statements.
 Note, if you supply this block, it must return integer value, zero upon success (this would be a good opportunity to use SQLITE_OK),
 non-zero value upon failure (which will stop the bulk execution of the SQL).  If a statement returns values, the block will be called with the results from the query in NSDictionary *resultsDictionary.
 This may be `nil` if you don't care to receive any results.
 
 @return `YES` upon success; `NO` upon failure.
 */
- (BOOL)executeStatements:(NSString *)sql withResultBlock:(nullable HZDBExecuteStatementsCallbackBlock)block;

/** 
 Begins a transaction.
 
 @param block The code to run database operations. Returns `YES` to commit transaction.
 
 @return `YES` on success; `NO` on failure.
 */
- (void)beginTransactionWithBlock:(BOOL(^)(HZDatabaseManager *db))block;

/** 
 Return `long` value for query.
 
 @param query The SQL query to be performed.
 
 @return `long` value.
 */

- (long)longForQuery:(NSString *)sql;

/**
 Return `string` value for query.
 
 @param query The SQL query to be performed.
 
 @return `string` value.
 */
- (NSString *)stringForQuery:(NSString *)sql;

/**
 Return `int` value for query.
 
 @param query The SQL query to be performed.
 
 @return `int` value.
 */
- (int)intForQuery:(NSString *)sql;

/**
 Return `double` value for query.
 
 @param query The SQL query to be performed.
 
 @return `double` value.
 */
- (double)doubleForQuery:(NSString *)sql;

/**
 Returns The rowid of the last inserted row.
 */
- (int64_t)lastInsertRowId;

/**
 Close database used by queue.
 */
- (void)close;

@end

NS_ASSUME_NONNULL_END
