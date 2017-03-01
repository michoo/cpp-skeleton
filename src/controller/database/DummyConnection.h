#include "ConnectionPool.h"
using boost::shared_ptr;

	class DummyConnection : public Connection {

	public:

		DummyConnection() {

		};

		~DummyConnection() {

		};

		// shared_ptr to some kind of actual connection object would go here

	};


	class DummyConnectionFactory : public ConnectionFactory {

	public:
		DummyConnectionFactory() {


		};

		// Any exceptions thrown here should be caught elsewhere
		shared_ptr<Connection> create() {

			// Create the connection
			shared_ptr<DummyConnection>conn(new DummyConnection());

			// Perform some kind of ->connect operation here

			return boost::static_pointer_cast<Connection>(conn);
		};

	};
