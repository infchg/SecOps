
## Using YAML to handle tokens JWT and keys JWKS

Storing JWT [RFC 7518](https://tools.ietf.org/html/rfc7518)and JWKS in Yaml improves readability and comments (see example after #%)

~~~json
keys:   #% JWKSet of 1 or more Keys shown as YAML here
  - kty: RSA   #% .. other types
    use: sig      #% -- or enc usage
    x5t: M2maFm3VYlMBOn3GetVWGXkrKrk
    kid: KEY_Alias
    x5c:    #% certificate chain
      - MIIE………(base64 encoded cert)………..zM=
      - MIIC………(base64 encoded cert)………..tow==
    alg: RS256     #% other algorthms
~~~

Such yaml does generate standard JWKs for RH SSO, Keycloak, others ( yq . JWKS.yaml > JWKS.json )

~~~json
	{
	  "keys": [
	    {
	      "kty": "RSA",
	      "use": "sig",
	      "x5t": "M2maFm3VYlMBOn3GetVWGXkrKrk",
	      "kid": "KEY_Alias",
	      "x5c": [
	        "MIIE………(base64 encoded cert)………..zM=",
	        "MIIC………(base64 encoded cert)………..tow=="
	      ],
	      "alg": "RS256"
	    }
	  ]
	}
~~~

When using RH SSO or Keycloak, we can then explore checking the introspect REST API:

	curl -XPOST -u "${CLIENT_ID}:${CLIENT_SECRET}" -d "token=${ACCESS_TOKEN}" "https://${KC_SERVER}/realms/${KC_REALM}/protocol/openid-connect/token/introspect"

JWT doesn’t have the Cross-Origin Resource Sharing (CORS) limitation cookies do when the token is sent in the Authorization header. Authorization: Bearer ${encoded_JWT}


## Identity providers - OpenIDs - GCP, Keycloak, Okta

Identity providers like Google, SAP IAS, Azure AD, Okta, Keycloak, AWS SSO, Auth0 ... allow SAML WebSSO or as OpenID Connect OIDC providers. 

With Google OpenAPI we can use a JWK set format or X509 locations:

	x-google-jwks_uri: x-google-jwks_uri: "https://ACC_NAME.AUTH_PROVIDER_URL/.well-known/jwks.json"
  	x-google-jwks_uri: "https://www.googleapis.com/service_accounts/v1/metadata/x509/securetoken@system.gserviceaccount.com"

To use standard OAuth2 / OpenID Connect client libraries, we should query Keycloak server for endpoints:

    curl -q http://$keycloakhost:$keycloakport/auth/realms/$realm/.well-known/openid-configuration | yq . -y  #% viasualize in YAML

It will return the Endpoints for OAuth2 Authorization , OAuth2 Token  and OpenID Connect UserInfo  :

~~~json
	#% |yq . -y
	issuer: http://localhost:8080/auth/realms/demo
	authorization_endpoint: http://localhost:8080/auth/realms/demo/protocol/openid-connect/auth
	token_endpoint: http://localhost:8080/auth/realms/demo/protocol/openid-connect/token
	userinfo_endpoint: http://localhost:8080/auth/realms/demo/protocol/openid-connect/userinfo
	end_session_endpoint: http://localhost:8080/auth/realms/demo/protocol/openid-connect/logout
	jwks_uri: http://localhost:8080/auth/realms/demo/protocol/openid-connect/certs
	grant_types_supported:
	  - authorization_code
	  - refresh_token
	  - password
	response_types_supported:
	  - code
	subject_types_supported:
	  - public
	id_token_signing_alg_values_supported:
	  - RS256
	response_modes_supported:
	  - query
~~~


### References

This document listed last ( InfChg/SecOps for International Sign-On)

- Google API https://cloud.google.com/endpoints/docs/openapi/openapi-extensions
- SAP Keycloak https://blogs.sap.com/2021/08/23/keyclock-as-an-openid-connect-oidc-provider./
- Propose modern (yaml) handling of Keys in Authentication Authorization against GCP Keycloak Okta@ Github.com/InfChg/SecOps 2022 https://github.com/infchg/GeoInt/blob/master/KeyCloack-yaml.md
- (inspired in lessons learned from reviewing compliance of cloud configs (NSGs) for Keycloak setups with GoTravel exchange of PNRs passenger records)
